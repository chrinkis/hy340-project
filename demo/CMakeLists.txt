include(flex_bison)

# For target al
add_executable(al
    lex/al/al.cpp

    ${CMAKE_SOURCE_DIR}/src/alpha/token/token.cpp
    ${CMAKE_SOURCE_DIR}/src/alpha/syntax/parser.cpp

    ${FLEX_BisonParser_OUTPUTS}
    ${FLEX_FlexScanner_OUTPUTS}
)

target_include_directories(al PRIVATE ${CMAKE_SOURCE_DIR}/include/alpha/syntax)
