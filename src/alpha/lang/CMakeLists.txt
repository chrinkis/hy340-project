# For target lang
add_executable(lang
    main.cpp

    $<TARGET_OBJECTS:flex_and_bison>
)
