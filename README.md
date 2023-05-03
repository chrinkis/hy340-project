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

## Build

Requirements:
- `CMake` (minimum version 3.18.4)
- `Flex` (tested on version 2.6.4)
- `Bison` (tested on version 3.8.2)
- `g++`

### al

Target `scanner` of cmake

### parser

Target `parser` of cmake

Alternatively, if `bash` is installed:
- Command: `bash compile.sh`
- Output: `build/demo/parser`

> *Note that parser uses `stdin` for input.*
> If you want to use a file, you could use bash redirections.

### Tests

*Don not run the unit test. They are out of date.*

> Unit Tests are **disabled** by default.

## For Developers

> *NOTE: TAs can skip this section*

See [CONTRIBUTING.md](CONTRIBUTING.md)
