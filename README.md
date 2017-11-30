# Contest Utilities
Manage your code library for competitions like [codeforces.com](http://codeforces.com).
- Work with many files and "copy-paste" them automatically, before submitting, with tool `cubuild`.
- Keep submitted file small - only actually included files are pasted.

## Installation
Requires Python >= 3.5, no other dependencies. To use, run `src/cubuild.py` in any directory. To add the script to
`$PATH` for a current user on Ubuntu >= 14.04, run `python3.5 install.py ~/bin`. You can now (or after doing `. ~/.profile`) use `cubuild` command.

## Usage
    cubuild source.cc -o source_all_in_single_file.cc -l path/to/your/includes/

### Example integration with make

Take a look at a README file in [examples/](examples/README.md) directory.
