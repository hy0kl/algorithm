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
    char *argv[] = {"./test"};
    EXPECT_EQ(0, parse_args(argc, argv));
}

TEST(work, workProcess)
{
    ACSM_STRUCT  *acsm = NULL;

    int argc = 3;
    char *argv[] = {
        "./test",
        "-p",
        "../src"
    };

    init_config();
    signal_setup();

    EXPECT_EQ(0, parse_args(argc, argv));
    EXPECT_EQ(0, init_acsm(&acsm));
    EXPECT_EQ(0, acsmCompile(acsm));
    printf("init PASS\n");

    struct evbuffer *buf;
    buf = evbuffer_new();
    g_vars.acsm = acsm;

    EXPECT_EQ(0, list_memory_pattern(buf));
    EXPECT_EQ(0, list_keyword(buf));
    printf("list function PASS\n");

    char word[1024] = "fuck";
    EXPECT_EQ(0, filter_process(word, 1, buf));
    snprintf(word, sizeof(word), "sb");
    EXPECT_EQ(0, filter_process(word, 1, buf));
    printf("filter process PASS\n");

    evbuffer_free(buf);
}
