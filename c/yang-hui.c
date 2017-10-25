/**
 * @describe: 杨辉三角
 * @see: http://www.cnblogs.com/clover-toeic/p/3766001.html
 * @author: Jerry Yang(hy0kle@gmail.com)
 * */
#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 10

/** 通过组合公式推导 */
void
BinomialYangHui(void)
{
    int dwRow = 0, dwCol = 0, dwTriVal;

    for (dwRow = 0; dwRow < MAX_ROW; dwRow++) {
        // 首列直接输出1，否则由二项式系数递推公式求出杨辉值
        dwTriVal = 1;
        for (dwCol = 0; dwCol <= dwRow; dwCol++) {
            printf("%5d", dwTriVal);
            dwTriVal = dwTriVal * (dwRow - dwCol) / (dwCol + 1);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    BinomialYangHui();

    return 0;
}

/* vim:set ft=c ts=4 sw=4 et fdm=marker: */

