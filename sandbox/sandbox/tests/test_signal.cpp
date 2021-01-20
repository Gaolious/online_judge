#include <gtest/gtest.h>
#include <inc/context.h>
#include <inc/child.h>

namespace TEST_SIGNAL {
    TEST(test_signal, divide_by_zero) {
        Context ctx;
        const char *argv[] = {
                "--uid=1",
                "--gid=2",
                "--memory=3",
                "--time=4",
                "--verbose",
                "--in=/tmp/in",
                "--out=/tmp/out",
                "--cmd=./sample_div_0"
        };
        int argc = sizeof(argv) / sizeof(argv[0]);

        g_ctx.initialize();
        g_ctx.parse(argc, (char **) argv);
        fork_child(&g_ctx);
    }
    TEST(test_signal, segment_fault) {
        Context ctx;
        const char *argv[] = {
                "--uid=1",
                "--gid=2",
                "--memory=3",
                "--time=4",
                "--verbose",
                "--in=/tmp/in",
                "--out=/tmp/out",
                "--cmd=./sample_sig_fault"
        };
        int argc = sizeof(argv) / sizeof(argv[0]);

        g_ctx.initialize();
        g_ctx.parse(argc, (char **) argv);
        fork_child(&g_ctx);
    }
}