# For target vm
add_executable(avm
    main.cpp

    abc/instruction/arg.cpp
    abc/instruction/instruction.cpp

    arch/cpu/cpu.cpp/execute/arithm.cpp
    arch/cpu/cpu.cpp/execute/bool.cpp
    arch/cpu/cpu.cpp/execute/etc.cpp
    arch/cpu/cpu.cpp/execute/func.cpp
    arch/cpu/cpu.cpp/execute/jumps.cpp
    arch/cpu/cpu.cpp/execute/table.cpp

    arch/cpu/cpu.cpp/behaviour.cpp

    arch/mem/cell.cpp

    arch/mem/code/table.cpp

    arch/mem/consts/consts.cpp
    arch/mem/consts/user_func.cpp

    arch/mem/stack/stack.cpp

    loader/loader.cpp

    runtime/libint/lib_functions.cpp

    runtime/messages/error.cpp

    runtime/table/table.cpp
)

target_include_directories(avm
    PUBLIC

    ${CMAKE_SOURCE_DIR}/include
)
