# For target vm
add_executable(vm
    main.cpp

    abc/instruction/arg.cpp
    abc/instruction/instruction.cpp

    arch/cpu/cpu.cpp

    arch/mem/cell.cpp

    arch/mem/code/table.cpp

    arch/mem/consts/consts.cpp
    arch/mem/consts/user_func.cpp

    arch/mem/stack/stack.cpp

    parser/parser.cpp

    runtime/libint/lib_functions.cpp

    runtime/messages/error.cpp

    runtime/table/table.cpp
)

target_include_directories(vm
    PUBLIC

    ${CMAKE_SOURCE_DIR}/include
)
