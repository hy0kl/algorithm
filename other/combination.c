/**
 * @describe:
 * @author: Jerry Yang(hy0kle@gmail.com)
 * @see: http://blog.csdn.net/w57w57w57/article/details/6657547
 * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
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

typedef unsigned long long int u_long_int;

u_long_int BIG1 = 1ULL;

/**
 * 给定一个正整数N，求最小的、比N大的正整数M，使得M与N的二进制表示中有相同数目的1。
 *
 */

/**
 * 计算给定的整型数的二进制表示中 1 的个数
 * 具体算法
 * 应用 n &= (n - 1) 能将 n 的二进制表示中的最右边的 1 翻转为 0
 * 只需要不停地执行 n &= (n - 1), 直到 n 变成 0 为止
 * 那么翻转的次数就是原来的 n 的二进制表示中 1 的个数.
 * */
int count1_bits(unsigned int n)
{
    int count = 0;

    while (n)
    {
        count++;
        n &= (n - 1);
    }

    return count;
}

/**
 * 高效算法
 * */
u_long_int  next_n(u_long_int N)
{
    u_long_int x = N & (-N);
    //printf("[%s] x = %llu\n", __func__, x);
    u_long_int t = N + x;
    //printf("[%s] t = %llu\n", __func__, t);
    u_long_int ans = t | ((N ^ t) / x) >> 2;
    //printf("[%s] ans = %llu\n", __func__, ans);

    return ans;
}

/**
 * 利用位操作求组合
 * 组合就是从N各对象中选取m个对象，问有多少种选法，并且要求输出每次的选法。
 * */
// 定义包含4个元素的集合
char set[] ={'a','b','c','d','e','f','g','h','i', 'j', 'k'};
char *mset[] ={
    "01", "02", "03", "04", "05",
    "06", "07", "08", "09", "10",
    "11", "12", "13", "14", "15",
    "16", "17", "18", "19", "20",
    "21", "22", "23", "24", "25",
    "26", "27", "28", "29", "30",
    "31", "32", "33"
};

size_t mset_size = sizeof(mset) / sizeof(*mset);

//根据C的二进制表示输出一个组合
void print(char* set, int C)
{
    int i = 0;
    int k;
    while ((k = 1 << i) <= C)
    {
        //循环测试每个bit是否为1
        if ((C & k) != 0)
        {
            printf("%c", set[i]);
        }

        i++;
    }
}

void mprint(char **mset, u_long_int C)
{
    int i = 0;
    u_long_int k;
    //printf("%s %lld\n", __func__, C);
    while ((k = BIG1 << i) <= C)
    {
        //循环测试每个bit是否为1
        //if (i < (sizeof(mset) / sizeof(*mset)) && (C & k) != 0)
        if (i < mset_size && (C & k) != 0)
        {
            //printf("%s i = %d\n", __func__, i);
            //printf("%d \t", i);
            printf("%s\t", mset[i]);
        }

        i++;
    }
}

//求从set中前N个元素 中选择m个的组合
void combination(char* set, int N, int m)
{
    u_long_int C = (BIG1 << m ) - 1;
    while (C <= (( BIG1 << N) - (BIG1 << (N - m))))
    {
        print(set, C);
        printf("\n");

        C = next_n(C);
    }
}

void mcombination(char **mset, int N, int m)
{
    u_long_int C = (BIG1 << m ) - BIG1;
    //printf("%s %lld\n", __func__, C);
    //printf("%d \n", (( 1 << N) - (1 << (N - m))));

    u_long_int diff = ((BIG1 << N) - (BIG1 << (N - m)));
    //printf("[%s] diff = %lld \n", __func__, diff);exit(-1);

    //while (C <= ((bit << N) - (bit << (N - m))))
    while (C <= diff)
    {
        mprint(mset, C);
        printf("\n");

        C = next_n(C);
        //printf("%s %lld\n", __func__, C);
    }
}


int main(int argc, char *argv[])
{
    //u_long_int t = 1ULL;
    //t = 1ULL << 33;
    //printf("t = %llu \n", t);

    //t = 0ULL << 32;
    //printf("t = %llu \n", t);

    //printf("%ld\n", sizeof(t));

    //combination(set, 8, 5);
    //printf("sizeof(mset) = %ld\n", sizeof(mset) / sizeof(*mset));

    // 双色球 33 红球选 6 个
    mcombination(mset, 33, 6);


    //u_long_int ret = next_n(2113929216ULL);

    return 0;
}

/* vi:set ft=c ts=4 sw=4 et fdm=marker: */

