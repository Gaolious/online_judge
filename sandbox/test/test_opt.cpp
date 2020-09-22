#include <gtest/gtest.h>

#include "../inc/opt.h"

TEST(test_OPTION, no_argumnet)
{
    OPTION option ;
    EXPECT_FALSE(parse_options(0, NULL, &option));
}

TEST(test_OPTION, valid_argumnet_without_verbose)
{
    OPTION option = {0, };

    const char *argv[] = {
        "--uid=1",
        "--gid=2",
        "--memory_limit=3",
        "--time_limit=4",
    };
    int argc = sizeof(argv) / sizeof(argv[0]);

    EXPECT_TRUE(parse_options(argc, (char **)argv, &option));
    EXPECT_EQ(option.uid, 1);
    EXPECT_EQ(option.gid, 2);
    EXPECT_EQ(option.memory_limit, 3);
    EXPECT_EQ(option.time_limit, 4);    
    EXPECT_EQ(option.verbose, false);

}
TEST(test_OPTION, valid_argumnet_with_verbose)
{
    OPTION option  ;

    const char *argv[] = {
        "--uid=1",
        "--gid=2",
        "--memory_limit=3",
        "--time_limit=4",
        "--verbose",
    };
    int argc = sizeof(argv) / sizeof(argv[0]);

    EXPECT_TRUE(parse_options(argc, (char **)argv, &option));
    EXPECT_EQ(option.uid, 1);
    EXPECT_EQ(option.gid, 2);
    EXPECT_EQ(option.memory_limit, 3);
    EXPECT_EQ(option.time_limit, 4);    
    EXPECT_EQ(option.verbose, true);
}