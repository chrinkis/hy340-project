include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests
    ${CMAKE_SOURCE_DIR}/test/test.cpp

    $<TARGET_OBJECTS:flex_and_bison>
)

target_link_libraries(tests
    PRIVATE Catch2::Catch2WithMain
)
