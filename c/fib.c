/**
 * @describe: 斐波那契数列
 * @see: https://zh.wikipedia.org/wiki/%E6%96%90%E6%B3%A2%E9%82%A3%E5%A5%91%E6%95%B0%E5%88%97
 * @author: Jerry Yang(hy0kle@gmail.com)
 * 数学上:
 * F(0) = 0
 * F(1) = 1
 * F(n) = F(n -1) + F(n - 2)
 *
 * # 常见的包装题:
 * 已知
 *   1. n 个台阶
 *   2. 一次只走一个或两个台阶
 * 求 共有多种走法
 * 误区: 很容易产生排列组合的错觉
 * 解法: 从1个台阶到5个台阶,写出所有的可能的走法
 * f(1) = [(1)], 1
 * f(2) = [(1, 1), (2)], 2
 * f(3) = [(1, 1, 1), (1, 2), (2, 1)], 3
 * f(4) = [(1, 1, 1, 1), (1, 1, 2), (1, 2, 1), (2, 1, 1), (2, 2)] 5
 * f(5) = [(1, 1, 1, 1, 1), (1, 1, 1, 2), (1, 1, 2, 1), (1, 2, 1, 1), (2, 1, 1, 1), (1, 2, 2), (2, 1, 2), (2, 2, 1)] 8
 * 数学归纳法发现,其本质是个斐波那契数列
 * */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/** 递归的解法 */
int
fib_recur(int n)
{
    assert(n >= 0);

    if (0 == n) {
        return 0;
    }else if (1 == n) {
        return 1;
    } else if (2 == n) {
        return 2;
    }

    return fib_recur(n - 1) + fib_recur(n - 2);
}

/** 迭代解法 */
int
fib(int n)
{
    assert(n >= 0);

    if (n <= 2) {
        return n;
    }

    int fib_f = 1;
    int fib_s = 2;

    for (int i = 3; i <= n; i++) {
        int fib_t = fib_f + fib_s;
        fib_f = fib_s;
        fib_s = fib_t;
    }

    return fib_s;
}

int main(int argc, char *argv[])
{
    int n = 7;

    printf("Fibonacci-recursion(%d) = %d\n", n, fib_recur(n));
    printf("Fibonacci-iter(%d)      = %d\n", n, fib(n));

    return 0;
}

/* vim:set ft=c ts=4 sw=4 et fdm=marker: */

