# For target al
add_executable(al
    lex/al/al.cpp

    $<TARGET_OBJECTS:flex_and_bison>
)
