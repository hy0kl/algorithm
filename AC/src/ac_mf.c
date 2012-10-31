/**
 * Author: hy0kle@gmail.com
 * NOTE: p += snprintf(p, buf_len - (p - buf), "</pre>");
 * 这种写法简单易读,但需要一个隐式的条件,那就是缓冲区足够大,
 * 能容纳下全部内容,否则可能出 core.
 */
#include "ac_mf.h"

config_t          gconfig;
global_variable_t g_vars;

int daemonize(int nochdir, int noclose)
{
    int fd;

    switch (fork())
    {
    case -1:
        return (-1);

    case 0:
        break;

    default:
        _exit(EXIT_SUCCESS);
    }

    if (setsid() == -1)
        return (-1);

    if (nochdir == 0)
    {
        if(chdir("/") != 0)
        {
            perror("chdir");
            return (-1);
        }
    }

    if (noclose == 0 && (fd = open("/dev/null", O_RDWR, 0)) != -1)
    {
        if (dup2(fd, STDIN_FILENO) < 0)
        {
            perror("dup2 stdin");
            return (-1);
        }
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("dup2 stdout");
            return (-1);
        }
        if (dup2(fd, STDERR_FILENO) < 0)
        {
            perror("dup2 stderr");
            return (-1);
        }

        if (fd > STDERR_FILENO)
        {
            if (close(fd) < 0)
            {
                perror("close");
                return (-1);
            }
        }
    }

    return(0);
}

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

    return;
}

static int filter_process(const char *data, int output_format, char *buf, const size_t buf_len)
{
    int   ret = 0;
    char *p   = NULL;
    ACSM_PATTERN * mlist = NULL;

    assert(NULL != buf);
    assert(buf_len > 1014);

    p = buf;
    *p = '\0';

    if (data)
    {
        clear_match_count();
        ret = acsmSearch(g_vars.acsm, (unsigned char *)data, strlen(data), PrintMatch);
        logprintf("acsmSearch() = %d", ret);
        mlist = g_vars.acsm->acsmPatterns;

        switch (output_format)
        {
        case OUTPUT_AS_JSON:    /** json */
            p += snprintf(p, buf_len - (p - buf), "\"stat\": [");

            for (; NULL != mlist; mlist = mlist->next)
            {
                if (! mlist->nmatch)
                {
                    continue;
                }

                p += snprintf(p, buf_len - (p - buf), "{\"keyword\": \"%s\", \"hit_count\": %d}, ",
                    mlist->nocase ? mlist->patrn : mlist->casepatrn, mlist->nmatch);
            }

            if (',' == *(p - 2))
            {
                p -= 2;
                *p = '\0';
            }
            p += snprintf(p, buf_len - (p - buf), "]");
            break;

        case OUTPUT_AS_HTML:    /** html */
        default:
            for (; NULL != mlist; mlist = mlist->next)
            {
                if (! mlist->nmatch)
                {
                    continue;
                }

                p += snprintf(p, buf_len - (p - buf), "<div>filter-key: %s, hit count: %d</div>",
                    mlist->nocase ? mlist->patrn : mlist->casepatrn, mlist->nmatch);
            }
            break;
        }
    }

    return ret;
}

static int build_html_body(const char *query, const char *data, char *buf, const size_t buf_len)
{
    assert(NULL != data);
    assert(NULL != buf);
    assert(buf_len > 128);

    int ret = 0;
    char *p = buf;
    *p = '\0';

    p += snprintf(p, buf_len - (p - buf), "<html><head><title>ac server demo</title></head>\
</head><body>\
<div>word: %s</div>\
<div>***filter result***</div>\
<div>%s</div>\
</body></html>",
        query ? query : "No input.", data);

    return ret;
}

static int build_json_body(const char *data, char *buf, const size_t buf_len)
{
    assert(NULL != data);
    assert(NULL != buf);
    assert(buf_len > 128);

    int ret = 0;
    char *p = buf;
    *p = '\0';

    p += snprintf(p, buf_len - (p - buf), "{\"error\": 0, %s}", data);

    return ret;
}

static int list_keyword(struct evbuffer *ev_buf)
{
    assert(NULL != ev_buf);

    int ret = 0;
    int fd = 0;
    struct stat stat_buf;
    size_t size = 0;
    char read_buf[1024 * 10] = {0};

    fd = open(gconfig.keyword_file, O_RDONLY);
    if (-1 == fd || 0 == fd)
    {
        evbuffer_add_printf(ev_buf, "Can NOT open('%s')\n", gconfig.keyword_file);
        ret = -1;
        goto FINISH;
    }

    if (0 != fstat(fd, &stat_buf))
    {
        evbuffer_add_printf(ev_buf, "Can get fstat()\n");
        ret = -1;
        goto STAT_ERR;
    }

    evbuffer_add_printf(ev_buf, "<pre>");
    // stat_buf.st_size;
    size = 0;
    ssize_t r_size = 0;
    while (size <= stat_buf.st_size)
    {
        lseek(fd, size, SEEK_SET);
        r_size = read(fd, read_buf, sizeof(read_buf) - 1);
        if (-1 == r_size)
        {
            break;
        }
        read_buf[r_size] = '\0';
        logprintf("read: [%s]", read_buf);
        evbuffer_add_printf(ev_buf, "%s", read_buf);

        size += r_size;
        if (0 == r_size)
        {
            break;
        }
    }
    evbuffer_add_printf(ev_buf, "</pre>");

STAT_ERR:
    close(fd);

FINISH:
    return ret;
}

static int list_memory_pattern(struct evbuffer *ev_buf)
{
    assert(NULL != ev_buf);

    int ret = 0;
    ACSM_PATTERN *mlist = NULL;

    evbuffer_add_printf(ev_buf, "<pre>\n"
            "---dump memory pattern---\n");
    mlist = g_vars.acsm->acsmPatterns;
    for (; NULL != mlist; mlist = mlist->next)
    {
        mlist->nmatch = 0;
        evbuffer_add_printf(ev_buf, "%s\n", mlist->patrn);
    }
    evbuffer_add_printf(ev_buf, "</pre>");

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
    int   do_action = ACTION_FILTER;
    char  tpl_buf[TPL_BUF_LEN]        = {0};
    char  work_buf[TPL_BUF_LEN]       = {0};
    char  post_buf[POST_DATA_BUF_LEN] = {0};
    char *p = NULL;
    char *pt   = NULL;
    char *find = NULL;

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

    /* 接收 GET 解析参数 */
    const char *word   = evhttp_find_header(&http_query, "word");
    const char *action = evhttp_find_header(&http_query, "action");
    const char *uri_format    = evhttp_find_header(&http_query, "format");

    if (NULL != action)
    {
        if (0 == strncmp(action, "list", 4))
        {
            do_action = ACTION_LIST;
        }
        else if (0 == strncmp(action, "memory", 6))
        {
            do_action = ACTION_MEMORY;
        }
    }

    if (uri_format && 0 == strncmp(uri_format, FORMAT_JSON, sizeof(FORMAT_JSON) - 1))
    {
        output_format = OUTPUT_AS_JSON;
    }

    /** 接受 PSOT 数据 */
    const char *post_data = (char *)EVBUFFER_DATA(req->input_buffer);
    if (post_data)
    {
        snprintf(post_buf, sizeof(post_buf), "%s", post_data);
        logprintf("POST: [%s]", post_buf);
        find = post_buf;
        if (NULL != (find = strstr(post_buf, "word=")))
        {
            find += 5;
            p = find;

            if (NULL != (pt = strchr(p, '&')))
            {
                *pt = '\0';
            }
        }
        word = find;
    }
#if (_DEBUG)
    else
    {
        logprintf("NO POST data.");
    }
#endif

    switch (do_action)
    {
    case ACTION_LIST:
        list_keyword(buf);
        break;

    case ACTION_MEMORY:
        list_memory_pattern(buf);
        break;

    case ACTION_FILTER:
    default:
        // portions handle
        filter_process(word, output_format, work_buf, sizeof(work_buf));

        /** build page */
        switch (output_format)
        {
            case OUTPUT_AS_JSON:
                build_json_body(work_buf, tpl_buf, sizeof(tpl_buf));
                break;

            case OUTPUT_AS_HTML:
            default:
                build_html_body(word, work_buf, tpl_buf, sizeof(tpl_buf));
                break;
        }
        break;
    }
    //处理输出header头
    evhttp_add_header(req->output_headers, "Content-Type", output_format ?
        "application/json; charset=UTF-8" :
            "text/html; charset=UTF-8");
    evhttp_add_header(req->output_headers, "Status", "200 OK");
    evhttp_add_header(req->output_headers, "Connection", "keep-alive");
    evhttp_add_header(req->output_headers, "Cache-Control", "no-cache");
    evhttp_add_header(req->output_headers, "Expires", "-1");
    evhttp_add_header(req->output_headers, "Server", SERVER_TAG);    /** libevent http server */

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

