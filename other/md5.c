#include <stdio.h>
#include <openssl/md5.h>
#include <string.h>

/**
 * gcc md5.c -o md5 -lcrypto
 * */

#define STR_BUF_LEN 2048

int main( int argc, char *argv[] )
{
    unsigned char data[STR_BUF_LEN] = "123abctest";
    unsigned char md[16];
    int i;
    char tmp[3] = {0};
    char buf[33]= {0};

    if (argc > 1 && argv[1][0])
    {
        snprintf((char *)data, STR_BUF_LEN, "%s", argv[1]);
    }

    MD5(data, strlen((char *)data), md);
    for (i = 0; i < 16; i++){
        sprintf(tmp, "%2.2x", md[i]);
        strcat(buf, tmp);
    }
    printf("md5(\"%s\") = %s\n", data, buf);

    return 0;
}
