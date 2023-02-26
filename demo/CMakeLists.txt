add_executable(al
    lex/al/al.c
    "${FLEX_FlexTarget_OUTPUTS}"
)
target_link_libraries(al LIB_token)
