# For Flex
include(flex-scanner)

# For target al
add_executable(al
    lex/al/al.c

    ${CMAKE_SOURCE_DIR}/src/collections/stack.c
    ${CMAKE_SOURCE_DIR}/src/alpha/token/alpha_token.c

    ${FLEX_FlexScanner_OUTPUTS}
)
