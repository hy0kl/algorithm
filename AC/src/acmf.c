/**
 * Author: hy0kle@gmail.com
 * NOTE: p += snprintf(p, buf_len - (p - buf), "</pre>");
 * 这种写法简单易读,但需要一个隐式的条件,那就是缓冲区足够大,
 * 能容纳下全部内容,否则可能出 core.
 */
#include "ac_mf.h"
#include "util.h"

int main (int argc, char **argv)
{
    struct evhttp *httpd = NULL;
    ACSM_STRUCT    *acsm = NULL;

    init_config();
    if (0 != parse_args(argc, argv))
    {
        fprintf(stderr, "parse args error.\n");
        goto FINISH;
    }
#if (_DEBUG)
    print_config();
#endif

    /** 信息屏蔽 */
    signal_setup();

    init_acsm(&acsm);
    /* Generate GtoTo Table and Fail Table */
    acsmCompile(acsm);
    g_vars.acsm = acsm;

    /** 初始化事件 */
    event_init();
    /** 初始化监听ip和端口 */
    // httpd = evhttp_start(proxy_listen, proxy_port);
    httpd = evhttp_start(gconfig.hostname, gconfig.port);
    if (NULL == httpd)
    {
        fprintf(stderr, "[Error]: Unable to listen on %s:%d\n",
            gconfig.hostname, gconfig.port);
        exit(1);
    }

    // 设置http连接超时时间
    evhttp_set_timeout(httpd, gconfig.timeout);
    // 设置请求到达后的回调函数
    evhttp_set_gencb(httpd, api_proxy_handler, NULL);
    // libevent 循环处理事件
    event_dispatch();

    // 释放资源
    evhttp_free(httpd);
    acsmFree(acsm);

FINISH:
    return (0);
}

