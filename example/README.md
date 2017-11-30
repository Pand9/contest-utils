## Example workspace

Example of integrating `cubuild` into your, humble contestant's, workflow.

- Every Codeforces task has its own subdirectory.
- Source file is always named `source.cc`. Build is managed by `make`. All commands are in `Makefile`,
including `cubuild` invocation, which generates `onefile.cc`.
- `onefile.cc` is a file that you submit to Codeforces.com. `onefile.e` is a target (and one of default ones)
compiled from `onefile.cc`, to check if everything works.
- There are also some "normal" targets: `release.e` ("e" like in "executable", unusual but convenient),
`debug.e` and `verbose.e`. These targets are built without `onefile.cc`, with includes.
- `Makefile` uses one environment variable: `cflib` - library of include files. `pactivate` file contains example of
how to setup this variable. You can put its contests in `~/.profile`, or in your contest's directory and write
`source pactivate`.

Have fun.