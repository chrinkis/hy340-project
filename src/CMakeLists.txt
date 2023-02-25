# For LIB_token
target_sources(LIB_token
    PRIVATE
        token/alpha_token.c
)

target_include_directories(LIB_token
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include/token
)

set_target_properties(LIB_token PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include/token"
)
