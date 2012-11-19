// Don't forget gtest.h, which declares the testing framework.

#include <limits.h>
#include "util.h"
#include "gtest/gtest.h"

TEST(daemonize, Zero)
{
    EXPECT_EQ(0, daemonize(1, 1));
}
