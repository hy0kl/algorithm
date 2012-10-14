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
    snprintf(gconfig.keyword_file, FILE_PATH_LEN, "%s", "./data/mf.keyword.txt");

    return ret;
}

int main (int argc, char **argv)
{
    int   i  = 0;
    FILE *fp = NULL;
    char  line[READ_LINE_BUF_LEN] = {0};
    char *p  = NULL;

    ACSM_STRUCT * acsm;

    init_config();

    acsm = acsmNew ();
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
        if (NULL != (p = strstr(p, "\n")))
        {
            *p = '\0'; 
        }

#if (_DEBUG)
        logprintf("line: [%s]", line);
#endif
    }

    //acsmAddPattern (acsm, argv[i], strlen (argv[i]), nocase);

    /* Generate GtoTo Table and Fail Table */
    //acsmCompile (acsm);

    /*Search Pattern*/
    /**
    while ( fgets(text,MAXLEN,fd) )
    {
        acsmSearch (acsm, text, strlen (text), PrintMatch);
        nline++;
    }

    PrintSummary(acsm->acsmPatterns);

    acsmFree (acsm);
    */

    return (0);
}

