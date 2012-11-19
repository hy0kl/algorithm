#ifndef _UTIL_H
#define _UTIL_H
#include  "ac_mf.h"

void usage(void);

int parse_args(int argc, char *argv[]);

void print_config(void);

int daemonize(int nochdir, int noclose);

void handler(int signo);

void signal_setup(void);

void init_config(void);

int init_acsm(ACSM_STRUCT **acsm);

void clear_match_count(void);

int filter_process(const char *data, int output_format, struct evbuffer *ev_buf);

int list_keyword(struct evbuffer *ev_buf);

int list_memory_pattern(struct evbuffer *ev_buf);

void api_proxy_handler(struct evhttp_request *req, void *arg);

#endif

