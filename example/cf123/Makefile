FLAGS_COMMON=-std=c++14 -Wall -Wextra -pedantic -Wshadow -Wfloat-equal -Wswitch-default -Winit-self
FLAGS_DEBUG=$(FLAGS_COMMON) -O0 -g -DDEBUG_PRINTS -coverage
FLAGS_RELEASE=$(FLAGS_COMMON) -O3

CC=g++-6

library=$(wildcard ${cflib}/*.h*)
headers=$(wildcard *.h*)
deps = source.cc Makefile $(library) $(headers)

default: debug.e

onefile.cc: $(deps)
	cubuild $< -o $@ -l ${cflib}

onefile.e: onefile.cc
	$(CC) $< -o $@ $(FLAGS_RELEASE)

debug.e: $(deps)
	$(CC) $< -o $@ ${FLAGS_DEBUG} -I${cflib}

verbose.e: $(deps)
	$(CC) $< -o $@ ${FLAGS_DEBUG} -DVERBOSE_PRINTS -I${cflib}

release.e: $(deps)
	$(CC) $< -o $@ ${FLAGS_RELEASE} -I${cflib}

all: $(default) onefile.e verbose.e release.e

coverage: debug.e
	lcov -d . -c > lcov.info
	genhtml lcov.info -o html
	firefox -new-window html/index.html

clean:
	rm -rf html *.e onefile.cc *.gcno *.gcda lcov.info
