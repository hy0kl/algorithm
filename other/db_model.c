/**
 * @describe:
 * @author: Jerry Yang(hy0kle@gmail.com)
 * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include <netdb.h>
#include <fcntl.h>
#include <time.h>
#include <assert.h>
#include <signal.h>
#include <errno.h>
#include <err.h>
#include <getopt.h>
#include <sys/time.h>
#include <sys/queue.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#define SQL_BUF_LEN     2048

static const char *demo_fields[] = {
    "id",
    "nickname",
    "mobile",
    "email",
    "create_time",
    NULL,
};

int main(int argc, char *argv[])
{
    size_t array_count = sizeof(demo_fields) / sizeof(char *);
    printf("array_count: %zu\n", array_count);

    char sql_buf[SQL_BUF_LEN];
    char *p = sql_buf;
    p += snprintf(p, SQL_BUF_LEN, "SELECT ");
    size_t i = 0;

    const char **field = demo_fields;
    for (; *field; field++, i++) {
        printf("field: %s, index: %zd\n", *field, i);
        p += snprintf(p, SQL_BUF_LEN - (p - sql_buf), "%s%s", i > 0 ? ", " : "", *field);
    }
    p += snprintf(p, SQL_BUF_LEN - (p - sql_buf), " FROM demo");
    printf("SQL: %s\n", sql_buf);

    return 0;
}

/* vim:set ft=c ts=4 sw=4 et fdm=marker: */

