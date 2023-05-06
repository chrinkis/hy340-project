# For target scanner
add_executable(scanner
    lex/al/al.cpp

    $<TARGET_OBJECTS:flex_and_bison>
)

# For target parser
add_executable(parser
    syntax/parser/main.cpp

    $<TARGET_OBJECTS:flex_and_bison>
)


# For target icode
add_executable(icode
    icode/main.cpp

    $<TARGET_OBJECTS:flex_and_bison>
)
