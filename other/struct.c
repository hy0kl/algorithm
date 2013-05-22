/**
 * @describe:
 * @author: hy0kle@gmail.com
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
#include <sys/types.h>
#include <sys/time.h>
#include <sys/queue.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

typedef struct _point_t
{
    int x;
    int y;
} point_t;

void dump(point_t p)
{
    printf("point.x = %d, point.y = %d\n", p.x, p.y);
}

inline point_t point_make(int x, int y)
{
    point_t p;

    p.x = x;
    p.y = y;

    return p;
}

int main(int argc, char *argv[])
{
    point_t p;
    p.x = 1;
    p.y = 22;

    point_t t = point_make(5, 99);

    dump(t);
    dump(p);

    return 0;
}

