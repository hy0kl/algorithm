/**
 * @describe:
 * @author: Jerry Yang(hy0kle@gmail.com)
 * */

#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int error_number;

    for (error_number = EPERM; error_number <= ELAST; error_number++) {
        printf("errno: %d\tstrerror: %s\n", error_number, strerror(error_number));
    }

    return 0;
}

/* vim:set ft=c ts=4 sw=4 et fdm=marker: */

