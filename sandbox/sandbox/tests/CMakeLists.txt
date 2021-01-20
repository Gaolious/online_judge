find_package(Threads REQUIRED)
find_package(GTest)

set(BINARY test_sb_opt)

FILE(GLOB SRCS "*.cpp")

add_executable(${BINARY} ${SRCS} test_child.cpp test_signal.cpp)

target_link_libraries(${BINARY} PUBLIC
    sandbox
    gtest
    gtest_main
    pthread
)

add_test(
    NAME ${BINARY}
    COMMAND ${BINARY}
)