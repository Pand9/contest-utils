#!/usr/bin/env python3
import argparse
import os
import shutil

import sys

import errno

from pathlib import Path


def ensure_dir(d):
    try:
        os.makedirs(d)
    except OSError as e:
        if e.errno != errno.EEXIST:
            raise

if __name__ == "__main__":
    def _run():
        me = Path(sys.argv[0]).parent
        p = argparse.ArgumentParser()
        p.add_argument("-t", "--target-bin-dir", required=True)
        args = p.parse_args()
        ensure_dir(args.target_bin_dir)
        shutil.copy(str(me / "src" / "cubuild.py"), str(Path(args.target_bin_dir) / "cubuild"))
    _run()