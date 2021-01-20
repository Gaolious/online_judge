#include <gtest/gtest.h>
#include <inc/child.h>


namespace CHILD_FORK
{
    TEST(test_child, test_sleep)
    {
        Context ctx ;
        const char *argv[] = {
                "--uid=1",
                "--gid=2",
                "--memory=3",
                "--time=4",
                "--verbose",
                "--in=/tmp/in",
                "--out=/tmp/out",
                "--cmd=./sample_sleep 0"
        };
        int argc = sizeof(argv) / sizeof(argv[0]);

        g_ctx.initialize();
        g_ctx.parse(argc, (char **) argv);
        fork_child(&g_ctx);
    }

    TEST(test_child, test_mem)
    {
        Context ctx ;
        const char *argv[] = {
                "--uid=1",
                "--gid=2",
                "--memory=3",
                "--time=4",
                "--verbose",
                "--in=/tmp/in",
                "--out=/tmp/out",
                "--cmd=./sample_mem 20000000"
        };
        int argc = sizeof(argv) / sizeof(argv[0]);

        g_ctx.initialize();
        g_ctx.parse(argc, (char **) argv);
        fork_child(&g_ctx);
    }

    TEST(test_child, test_java)
    {
        Context ctx ;
        const char *argv[] = {
                "--uid=1",
                "--gid=2",
                "--memory=3",
                "--time=4",
                "--verbose",
                "--in=/tmp/in",
                "--out=/tmp/out",
                "--cmd=./test.sh"
        };
        int argc = sizeof(argv) / sizeof(argv[0]);

        g_ctx.initialize();
        g_ctx.parse(argc, (char **) argv);
        fork_child(&g_ctx);
    }
}
