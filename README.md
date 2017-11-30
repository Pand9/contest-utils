Documentation - work in progress. If you are interested, please contact me, I'll help you.

# Contest Utilities
Manage your code library for competitions like [codeforces.com](http://codeforces.com).
- Work with many files and "copy-paste" them automatically, before submitting, with utility `cubuild`.
- Keep submitted file small - only actually included files are pasted by `cubuild`.

## Future plans
- Protect your code library from regressions by using solved problems as regression tests.
All you have to do is download tests from contest's page and point them to `cu`.

#### Todo
- example/: add Makefile and dir structure
- workspace generator
- usage docs
- `cusubmit`: wrapper for Codeforces API, with potential to be extensible for other sites
- convenient adding hand-written tests
- support in example/Makefile for many source files
- `culibtest add`, `culibtest run` `culibtest list` - library tests based on solved problems  


##### Fixes
- deliver lib path from command line, instead of file - so that it can be defined in on place, e.g. shell variable
