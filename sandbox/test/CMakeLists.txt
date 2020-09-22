cmake_minimum_required(VERSION 3.10)


set(This SandboxTest)

set(Sources
    test_opt.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    Sandbox
    gtest
    gtest_main
    pthread
)

add_test(
    NAME ${This}
    COMMAND ${This}
)