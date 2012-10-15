/**
 * Author: hy0kle@gmail.com
 */
#include "ac_mf.h"

config_t          gconfig;
global_variable_t g_vars;

static int init_config()
{
    int ret = 0;

    gconfig.log_level = 4;
    gconfig.no_case   = 1;
    gconfig.port      = 8668;
    gconfig.timeout   = 1;

    snprintf(gconfig.hostname, HOST_NAME_LEN, "%s", "0.0.0.0");
    snprintf(gconfig.keyword_file, FILE_PATH_LEN, "%s", "./data/mf.keyword.txt");

    return ret;
}

static int init_acsm(ACSM_STRUCT **acsm)
{
    int ret = 0;

    FILE *fp = NULL;
    char  line[READ_LINE_BUF_LEN] = {0};
    char *p  = NULL;

    *acsm = acsmNew();
    fp   = fopen(gconfig.keyword_file, "r");
    if (fp == NULL)
    {
        fprintf(stderr,"Open file error: %s\n", gconfig.keyword_file);
        exit(1);
    }

    while (! feof(fp))
    {
        if (NULL == fgets(line, READ_LINE_BUF_LEN - 1, fp))
        {
            continue;
        }

        line[READ_LINE_BUF_LEN - 1] = '\0';
        if (NULL != (p = strstr(line, "\n")))
        {
            *p = '\0';
        }

#if (_DEBUG)
        logprintf("line: [%s]", line);
#endif
        acsmAddPattern(*acsm, (unsigned char *)line, strlen(line), gconfig.no_case);
    }

    return ret;
}

static void clear_match_count()
{
    ACSM_PATTERN *mlist = NULL;

    mlist = g_vars.acsm->acsmPatterns;
    for (; NULL != mlist; mlist = mlist->next)
    {
        mlist->nmatch = 0;
    }
}

static int  filter_process(const char *data, char *buf, const size_t buf_len)
{
    int   ret = 0;
    char *p   = NULL;
    ACSM_PATTERN * mlist = NULL;

    assert(NULL != buf);
    assert(buf_len > 1014);

    p = buf;
    p += snprintf(p, buf_len - (p - buf), "<html><head><title>ac server demo</title></head>\
</head><body><div>word: %s</div><div>***filter result***</div><div>",
        data ? data : "No input.");

    if (data)
    {
        clear_match_count();
        ret = acsmSearch(g_vars.acsm, (unsigned char *)data, strlen(data), PrintMatch);
        logprintf("acsmSearch() = %d", ret);
        mlist = g_vars.acsm->acsmPatterns;
        for (; NULL != mlist; mlist = mlist->next)
        {
            if (! mlist->nmatch)
            {
                continue;
            }


            if (mlist->nocase)
            {
                p += snprintf(p, buf_len - (p - buf), "<div>filter-key: %s, hit count: %d</div>",
                        mlist->patrn, mlist->nmatch);
            }
            else
            {
                p += snprintf(p, buf_len - (p - buf), "<div>filter-key: %s, hit count: %d</div>",
                        mlist->casepatrn, mlist->nmatch);
            }
        }
    }

    p += snprintf(p, buf_len - (p - buf), "</div></body></html>");

    return ret;
}

static void api_proxy_handler(struct evhttp_request *req, void *arg)
{
    // 初始化返回客户端的数据缓存
    struct evbuffer *buf;
    buf = evbuffer_new();

    /* 分析URL参数 */
    char *decode_uri = strdup((char*) evhttp_request_uri(req));
    struct evkeyvalq http_query;
    evhttp_parse_query(decode_uri, &http_query);

    int   output_format = 0;
    char  tpl_buf[POST_DATA_BUF_LEN] = {0};

#if (_DEBUG)
    logprintf("uri: %s", decode_uri);
#endif

    /** free memory */
    free(decode_uri);

#if (_DEBUG)
#ifdef TAILQ_FOREACH
    //遍历整个uri的对应关系值
    {
        logprintf("--- foreach uri ---");
        struct evkeyval *header;
        TAILQ_FOREACH(header, &http_query, next) {
            logprintf("%s: %s", header->key, header->value);
        }
        logprintf("--- end uri ---");
    }
    //遍历整个请求头.
    {
        logprintf("---- foreach request header ----");
        struct evkeyvalq *input_headers = evhttp_request_get_input_headers(req);
        struct evkeyval *header;
        TAILQ_FOREACH(header, input_headers, next) {
            logprintf("%s: %s", header->key, header->value);
        }
        logprintf("---- end request header ----");
    }
#endif
#endif

    /* 接收 GET 解析参数 { */
    const char *word   = evhttp_find_header(&http_query, "word");

    // portions handle
    filter_process(word, tpl_buf, POST_DATA_BUF_LEN);

    //处理输出header头
    evhttp_add_header(req->output_headers, "Content-Type", output_format ?
        "application/json; charset=UTF-8" :
            "text/html; charset=UTF-8");
    evhttp_add_header(req->output_headers, "Status", "200 OK");
    evhttp_add_header(req->output_headers, "Connection", "keep-alive");
    evhttp_add_header(req->output_headers, "Cache-Control", "no-cache");
    evhttp_add_header(req->output_headers, "Expires", "-1");
    evhttp_add_header(req->output_headers, "Server", "lhs");    /** libevent http server */

    //处理输出数据
    evbuffer_add_printf(buf, "%s", tpl_buf);

    //返回code 200
    evhttp_send_reply(req, HTTP_OK, "OK", buf);

    //释放内存
    evhttp_clear_headers(&http_query);
    evbuffer_free(buf);

    return;

}

int main (int argc, char **argv)
{
    struct evhttp *httpd = NULL;
    ACSM_STRUCT    *acsm = NULL;

    init_config();

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

    return (0);
}

