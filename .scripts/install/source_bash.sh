#!/bin/bash

# This script allows you to use `al` and `avm` directly in a bash session.
#
# requirements:
#   - project was built in the `build` dir in the root of the project
#   - you source the script from the root of the project
#
# examples:
#   - `. .scripts/install/source_bash.sh`
#   - `source .scripts/install/source_bash.sh`
#
# notes:
#   - This script was created to help developers in testing

ALPHA_LANG_PATH=$(pwd)

function al {
    ${ALPHA_LANG_PATH}/build/src/alpha/lang/lang
}

function avm {
    ${ALPHA_LANG_PATH}/build/src/alpha/vm/vm
}
