#ifndef _AC_MF_H
#define _AC_MF_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <arpa/inet.h>
#include <openssl/md5.h>

/**
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
*/
#include "acsmx.h"

#define _DEBUG  1

#define POST_DATA_BUF_LEN   2048
#define FILE_PATH_LEN       256
#define READ_LINE_BUF_LEN   1024

#define logprintf(format, arg...) fprintf(stderr, "[NOTICE]%s:%d:%s "format"\n", __FILE__, __LINE__, __func__, ##arg)

typedef struct _global_variable_t
{
    char post_data[POST_DATA_BUF_LEN];
} global_variable_t;

typedef struct _config_t
{
    int  log_level;
    int  no_case;
    char keyword_file[FILE_PATH_LEN];
}  config_t;

extern global_variable_t g_vars;
extern config_t gconfig;

#endif

