# For Flex
include(flex-scanner)

# For target al
add_executable(al
    lex/al/al.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/token/token.cpp

    ${FLEX_FlexScanner_OUTPUTS}
)
