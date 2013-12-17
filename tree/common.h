#ifndef __COMMON_H__
#define __COMMON_H__

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

/** 宏形式 */
#define GREEN    "\e[1;32m"
#define BLUE     "\e[1;34m"
#define YELLOW   "\e[1;33m"
#define RED      "\e[1;31m"

/** const 指针形式 */
char *MAGENTA  = "\e[01;35m";
char *CYAN     = "\e[01;36m";
char *NORMAL   = "\e[0m";

#define logprintf(format, arg...) fprintf(stderr, "%s[LOG]%s %s:%d:%s "format"\n",\
        RED, NORMAL,__FILE__, __LINE__, __func__, ##arg)

#endif
