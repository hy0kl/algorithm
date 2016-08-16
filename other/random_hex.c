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

#define BUF_LEN 64

int main(int argc, char *argv[])
{
    char out_buf[BUF_LEN + 1] = {0};
    printf("sizeof(out_buf): %u\n", sizeof(out_buf));

    FILE *fp      = fopen("/dev/urandom", "r");
    char *charset = "0123456789abcdef";
    unsigned int j;

    if (fp == NULL || fread(out_buf, BUF_LEN, 1,fp) == 0) {
        printf("Can not open file: /dev/urandom.\n");
        exit(0);
    }

    for (j = 0; j < BUF_LEN; j++)
        out_buf[j] = charset[out_buf[j] & 0x0F];
    if (fp) fclose(fp);

    printf("random_hex: %s\n", out_buf);

    return 0;
}

/* vim:set ft=c ts=4 sw=4 et fdm=marker: */

