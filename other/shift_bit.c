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
#include <sys/types.h>
#include <sys/time.h>
#include <sys/queue.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[])
{
    int i;

    for (i = 0; i < 32; i++)
    {
        printf("1 << %d\t= %ld\n", i, (long int)(1L << i));
    }


    printf("1 | 2  = %d\n", 1 | 2);
    printf("1 | 2 | 4 = %d\n", 1 | 2 | 4);
    return 0;
}

/* vi:set ft=c ts=4 sw=4 et fdm=marker: */

