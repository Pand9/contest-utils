#!/usr/bin/env python3

import argparse
import json
import logging

import os
from fnmatch import fnmatch
from pathlib import Path

import datetime

def_h_extensions = ["h", "hpp"]


def open_read(filepath: Path):
    return open(str(filepath), "r", encoding="utf8")

def open_write(filepath: Path):
    return open(str(filepath), "w", encoding="utf8")


class ResolveError(Exception):
    def __init__(self, dirs, header_path):
        self._dirs = dirs
        self._header_path = header_path

    def __str__(self):
        return "Cannot resolve include %s in any of %s" % (self._header_path, self._dirs)


class HeaderResolver:
    def __init__(self, lib_dir: Path, local_dir: Path):
        self._lib_dir = lib_dir
        self._local_dir = local_dir

    def resolve(self, header_path):
        for d in self._local_dir, self._lib_dir:
            if (d / header_path).is_file():
                return d / header_path
        raise ResolveError([self._lib_dir, self._local_dir], header_path)


class LineDefinition:
    def matches(self, line):
        raise NotImplementedError()


class CaptureError(Exception):
    def __init__(self, rule, line_def: LineDefinition):
        self.rule = rule
        self.line_def = line_def

    def __str__(self):
        return "Error capturing %s in line %s" % (self.rule, self.line_def)


class ParametrizedLineDefinition(LineDefinition):
    def __init__(self, start, end):
        self._start = start
        self._end = end

    def matches(self, line):
        return line.startswith(self._start)

    def capture(self, line):
        index_start = len(self._start)
        index_end = line.find(self._end, len(self._start))
        if index_end == -1:
            raise CaptureError(self, line)
        return line[index_start:index_end]

    def stringify(self, value):
        return self._start + value + self._end

    def __str__(self):
        return self.stringify("...")


class FixedLineDefinition(LineDefinition):
    def __init__(self, pattern):
        self._pattern = pattern

    def matches(self, line):
        return fnmatch(line, self._pattern)

    def stringify(self):
        return str(self)

    def __str__(self):
        return self._pattern


class StructureDefinitions:
    user_include = ParametrizedLineDefinition('#include "', '"')
    pragma = FixedLineDefinition("#pragma once")
    using_namespace = ParametrizedLineDefinition("using namespace ", ";")
    system_include = ParametrizedLineDefinition('#include <', '>')

    default_include_path = "bits/stdc++.h"
    namespace = "std"

    skip_in_headers = [user_include, using_namespace, pragma, system_include]

    @classmethod
    def get_file_header(cls):
        yield "// %s" % datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        yield cls.system_include.stringify(cls.default_include_path)
        yield cls.using_namespace.stringify(cls.namespace)


class CPPFile:
    def __init__(self, filepath: Path):
        self._filepath = filepath

    def _iterlines(self):
        with open_read(self._filepath) as f:
            for line in f:
                yield line.rstrip()

    def read_deps(self):
        for line in self._iterlines():
            if StructureDefinitions.user_include.matches(line):
                yield StructureDefinitions.user_include.capture(line)

    def get_content_for_onefile(self):
        for line in self._iterlines():
            try:
                skip = False
                for line_to_skip in StructureDefinitions.skip_in_headers:
                    if line_to_skip.matches(line):
                        skip = True
                if not skip:
                    yield line
            except CaptureError as e:
                logging.error(e)
                raise

def run(libdir: Path, input_file_path: Path, output_file_path: Path):
    resolver = HeaderResolver(libdir, input_file_path.parent)
    visited_filenames = set()
    onefile = []
    onefile.extend(StructureDefinitions.get_file_header())

    def _rec(p):
        if p in visited_filenames:
            return
        visited_filenames.add(p)
        cppfile = CPPFile(p)
        for dep in cppfile.read_deps():
            _rec(resolver.resolve(dep))
        onefile.extend(cppfile.get_content_for_onefile())

    _rec(input_file_path)

    with open_write(output_file_path) as f:
        f.write("\n".join(onefile))

if __name__ == "__main__":
    def _run():
        p = argparse.ArgumentParser()
        p.add_argument("source", help="Path to source file to build")
        p.add_argument("-o", "--target-singlefile", required=True, help="Path to a target single file")
        p.add_argument("-l", "--includes-lib", required=True, help="Path to include library")
        p.add_argument("-v", "--verbose", action="store_true")
        args = p.parse_args()
        logging.basicConfig(level=logging.INFO if args.verbose else logging.WARNING, format="%(message)s")
        run(Path(args.includes_lib), Path(args.source), Path(args.target_singlefile))
    _run()