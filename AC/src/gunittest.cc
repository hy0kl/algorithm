// Don't forget gtest.h, which declares the testing framework.

#include <limits.h>
#include "util.h"
#include "gtest/gtest.h"

TEST(daemonize, setDaemon)
{
    EXPECT_EQ(0, daemonize(1, 1));
}

TEST(parse_args, parseArgs)
{
    int argc = 1;
    char *argv[32] = {{"./test"}};
    EXPECT_EQ(0, parse_args(argc, argv));
}

