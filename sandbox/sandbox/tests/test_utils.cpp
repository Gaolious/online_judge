#include <gtest/gtest.h>

#include <inc/utils.h>

namespace TEST_STRIPS
{
    struct param {
        const char *in ;
        const char *out ;
    };

    class Util_lstrip : public ::testing::TestWithParam<param>
    {};

    TEST_P(Util_lstrip, TestLeftStripWithGivenData)
    {
        param data = GetParam();
        char *buf = strdup(data.in);

        char *ret = lstrip(buf, "\t\r\n ");

        ASSERT_STREQ(ret, data.out);

        free(buf);
    }

    INSTANTIATE_TEST_CASE_P(test_lstrip, Util_lstrip, testing::Values(
            param{
                    .in = "asdf",
                    .out = "asdf"
            },
            param{
                    .in = "\tasdf",
                    .out = "asdf"
            },
            param{
                    .in = "\t              asdf",
                    .out = "asdf"
            },
            param{
                    .in = "\r\n\t              asdf",
                    .out = "asdf"
            },
            param{
                    .in = "\r\n\t",
                    .out = ""
            }
        )
    );

    class Util_rstrip : public ::testing::TestWithParam<param>
    {};

    TEST_P(Util_rstrip, TestRightStripWithGivenData)
    {
        param data = GetParam();
        char *buf = strdup(data.in);

        char *ret = rstrip(buf, "\t\r\n ");

        ASSERT_STREQ(ret, data.out);

        free(buf);
    }

    INSTANTIATE_TEST_CASE_P(test_rstrip, Util_rstrip, testing::Values(
            param{
                    .in = "asdf",
                    .out = "asdf"
            },
            param{
                    .in = "asdf\t",
                    .out = "asdf"
            },
            param{
                    .in = "asdf\t              ",
                    .out = "asdf"
            },
            param{
                    .in = "asdf\r\n\t              ",
                    .out = "asdf"
            },
            param{
                    .in = "\r\n\t",
                    .out = ""
            },
            param{
                    .in = "\r\n\t              asdf",
                    .out = "\r\n\t              asdf"
            }
    )
    );
}