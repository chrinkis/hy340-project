# For target vm
add_executable(vm
    main.cpp

    abc/instruction/arg.cpp
    abc/instruction/instruction.cpp

    arch/cpu.cpp/execute/arithm.cpp
    arch/cpu.cpp/execute/bool.cpp
    arch/cpu.cpp/execute/etc.cpp
    arch/cpu.cpp/execute/func.cpp
    arch/cpu.cpp/execute/jumps.cpp
    arch/cpu.cpp/execute/table.cpp

    arch/cpu.cpp/behaviour.cpp

    arch/mem/cell.cpp

    arch/mem/code/table.cpp

    arch/mem/consts/consts.cpp
    arch/mem/consts/user_func.cpp

    arch/mem/stack/stack.cpp

    runtime/libint/lib_functions.cpp

    runtime/messages/error.cpp

    runtime/table/table.cpp
)

target_include_directories(vm
    PUBLIC

    ${CMAKE_SOURCE_DIR}/include
)
