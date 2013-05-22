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
    point_t p;  /** 开辟内存 */
    p.x = 1;
    p.y = 22;

    /** 开辟一块新内存 */
    point_t t = point_make(5, 99);

    dump(t);
    dump(p);

    /**
     * 将 &t 指向的内存中内容拷贝到 &p 指向的内存中
     * 此时 t 和 p 拥有同样的内容
     * p 原来的内容被覆盖
     * */
    p = t;
    dump(p);

    return 0;
}

