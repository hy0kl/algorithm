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

#include <event.h>
#include <evhttp.h>

/**
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
*/
#include "acsmx.h"

#define _DEBUG  1

#define PACKAGE     "ac-mf"
#define VERSION     "0.0.1"

#define SERVER_TAG          "eac v 0.0.1"
#define POST_DATA_BUF_LEN   1024 * 20
#define FILE_PATH_LEN       256
#define READ_LINE_BUF_LEN   1024
#define HOST_NAME_LEN       32

#define ACTION_FILTER   1
#define ACTION_LIST     2
#define ACTION_MEMORY   3

/** output format */
#define OUTPUT_AS_HTML 0
#define OUTPUT_AS_JSON 1

#define CRLF    "<br />"
#define FORMAT_HTML "html"
#define FORMAT_JSON "json"

#define DEFAULT_LOG_LEVEL   4   /** unused */
#define DEFAULT_TIMEOUT     1
#define DEFAULT_HOSTNAME    "0.0.0.0"
#define DEFAULT_PORT        8668
#define DEFINE_KEYWORD_FILE "mf.keyword.txt"
#define DEFAULT_PREFIX      "."
#define DEFAULT_CASE_SWITCH 1

#if defined(__DATE__) && defined(__TIME__)
static const char build_date[] = __DATE__ " " __TIME__;
#else
static const char build_date[] = "unknown";
#endif

#define logprintf(format, arg...) fprintf(stderr, "[NOTICE]%s:%d:%s "format"\n", __FILE__, __LINE__, __func__, ##arg)

typedef struct _global_variable_t
{
    ACSM_STRUCT *acsm;
    char post_data[POST_DATA_BUF_LEN];
} global_variable_t;

typedef struct _config_t
{
    int  log_level;
    int  no_case;
    int  port;
    int  timeout;
    char prefix[FILE_PATH_LEN];
    char hostname[HOST_NAME_LEN];
    char keyword_file[FILE_PATH_LEN];
}  config_t;

extern global_variable_t g_vars;
extern config_t gconfig;

#endif

