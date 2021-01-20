#include <gtest/gtest.h>

#include <inc/context.h>

TEST(Context_Option, no_argumnet)
{
    Context option ;
    EXPECT_FALSE(option.parse(0, NULL));
}

TEST(Context_Option, valid_argumnet_without_verbose)
{
    Context option;

    const char *argv[] = {
        "--uid=1",
        "--gid=2",
        "--memory=3",
        "--time=4",
        "--in=/tmp/in",
        "--out=/tmp/out",
        "--cmd='/bin/ls -al'"
    };
    int argc = sizeof(argv) / sizeof(argv[0]);

    EXPECT_TRUE(option.parse(argc, (char **) argv));
    EXPECT_EQ(option.uid, 1);
    EXPECT_EQ(option.gid, 2);
    EXPECT_EQ(option.memory_limit, 3);
    EXPECT_EQ(option.time_limit, 4);    
    EXPECT_EQ(option.log_level, LOG_LEVEL::DEBUG);

    EXPECT_STREQ(option.in_path, "/tmp/in");
    EXPECT_STREQ(option.out_path, "/tmp/out");
    EXPECT_STREQ(option.cmd_path, "/bin/ls -al");
}

TEST(Context_Option, valid_argumnet_with_verbose)
{
    Context option  ;

    const char *argv[] = {
        "--uid=1",
        "--gid=2",
        "--memory=3",
        "--time=4",
        "--verbose",
        "--in=/tmp/in",
        "--out=/tmp/out",
        "--cmd=/bin/ls"
    };
    int argc = sizeof(argv) / sizeof(argv[0]);

    EXPECT_TRUE(option.parse(argc, (char **) argv));
    EXPECT_EQ(option.uid, 1);
    EXPECT_EQ(option.gid, 2);
    EXPECT_EQ(option.memory_limit, 3);
    EXPECT_EQ(option.time_limit, 4);
    EXPECT_EQ(option.log_level, LOG_LEVEL::INFO);

    EXPECT_STREQ(option.in_path, "/tmp/in");
    EXPECT_STREQ(option.out_path, "/tmp/out");
    EXPECT_STREQ(option.cmd_path, "/bin/ls");
}