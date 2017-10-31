/**
 * @describe: atoi 函数实现
 * @see: http://blog.csdn.net/u014082714/article/details/44775269
 * @author: Jerry Yang(hy0kle@gmail.com)
 * */
#include <stdio.h>

/** 来自 linux内核的 atoi 函数实现 */
static int local_atoi(const char *name)
{
    int val = 0;

    for (;; name++) {
        switch (*name) {
        case '0' ... '9':
            val = 10 * val + (*name - '0');
            break;
        default:
            return val;
        }
    }
}

int
isspace(int x)
{
    if (x ==' '|| x == '\t' || x == '\n' || x == '\f' || x == '\b' || x == '\r')
        return 1;
    else
        return 0;
}

int
isdigit(int x)
{
    if (x <= '9' && x >= '0')
        return 1;
    else
        return 0;

}

int
atoi(const char *nptr)
{
    int c;              /* current char */
    int total;          /* current total */
    int sign;           /* if '-', then negative, otherwise positive */

    /* skip whitespace */
    while (isspace((int)(unsigned char)*nptr))
        ++nptr;

    c = (int)(unsigned char)*nptr++;
    sign = c;           /* save sign indication */
    if (c == '-' || c == '+')
        c = (int)(unsigned char)*nptr++;    /* skip sign */

    total = 0;

    while (isdigit(c)) {
        total = 10 * total + (c - '0');     /* accumulate digit */
        c = (int)(unsigned char)*nptr++;    /* get next char */
    }

    if (sign == '-')
        return -total;
    else
        return total;   /* return result, negated if necessary */
}

int main(int argc, char *argv[])
{
    char *num = "1024";
    char *s_num = "-1024";
    printf("local_atoi(\"%s\") = %d\n", num, local_atoi(num));
    printf("atoi(\"%s\") = %d\n", s_num, atoi(s_num));

    return 0;
}

/* vim:set ft=c ts=4 sw=4 et fdm=marker: */

