## Repository status

This repository is an unmaintained mirror of the repository
[niex/hy340-project](https://gitlab-csd.datacenter.uoc.gr/niex/hy340-project).

## Table of contents

- [Developers](#developers)
- [Notes per phase](#notes-per-phase)
- [Build](#build)
- [For developers (TAs can skip this)](#for-developers)

## Developers

- Nikolaos Grigoroudis, csd4619@csd.uoc.gr
- Alexandros Christinakis, csd4764@csd.uoc.gr

## Notes per phase

### Phase I

- The project was implemented according to the project guidelines
- Things that were not implemented: None

### Phase II

- We re-wrote the project (phase I) in `C++`
- The project was implemented according to the project guidelines
- Things that were not implemented: None
- Error message could be more descriptive

### Phase III

- The project was implemented according to the project guidelines
- Things that were not implemented:
  1. Short circuit evaluation

### Phase VI

- The project was implemented according to the project guidelines
- Everything should work correctly.

### Phase V

- The project was implemented according to the project guidelines
- Extra implementations:
  - library functions:
    - [X] `input`
    - [X] `objectmemberkeys`
    - [X] `objecttotalmembers`
    - [X] `objectcopy`
    - [X] `strtonum`
    - [X] `sqrt`
    - [X] `cos`
    - [X] `sin`
  - types for table-indexes:
    - [X] `bool`
    - [X] `table`
    - [X] `user_func`
    - [X] `lib_func`
- In case of `table[index] = nil;`, the element (if exists) will be deleted from
the table, but there is a warning due to an extra `getelement` instruction for
a temporary variable.
- By default, the return value register of the virtual machine has `nil` value.
In other words, functions that do not return a value explicitly, will return `nil`
implicitly.
- When there are variables in the `program variable scopespace` that are not global,
the stack of the virtual machine does not reserve place for them. In order to avoid
problems, you could use a `main` function for your program. This could be fixed by 
providing the virtual machine (through the input file)  with the number of the 
varibles mentioned above (unfortunately, there was no time to implement it).

## Build

### Requirements
- `Bison` (tested on version 3.8.2)
- `CMake` (minimum version 3.18.4)
- `Flex` (tested on version 2.6.4)
- `g++`

### Steps
1. `mkdir build`
2. `cd build`
3. `cmake ..`
4. `make`

This will built:
- the compiler: `build/src/alpha/lang/al`
- the virtual machine: `build/src/alpha/vm/avm`

### Run

You can compile an alpha source code file with:
- `al <alpha_source_code>`

This will produce two files:
1. `out.abc`
2. `out.txt`

Then, you can run either of the above files with:
- `avm <out.abc>` or `avm <out.txt>`

### Tests

*Don not run the unit test. They are out of date.*

> Unit Tests are **disabled** by default.

## For Developers

> *NOTE: TAs can skip this section*

See [CONTRIBUTING.md](CONTRIBUTING.md)
