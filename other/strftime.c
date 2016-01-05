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

#define BUFLEN 256

int main(int argc, char *argv[])
{
    time_t t = time(NULL);   
    char buf[BUFLEN];   
    strftime(buf, BUFLEN, "%Y-%m-%d %H:%M:%S", localtime(&t)); //format date and time. 
    printf("Date-Tims: %s\n", buf);

    return 0;
}

/* vim:set ft=c ts=4 sw=4 et fdm=marker: */

