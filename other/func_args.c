/**
 * @describe:
 * @author: hy0kle@gmail.com
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
/**
 * 一个例子充分理解 C 语言的函数调用时形参与实参的关系,
 * 以及对于传值和传引用的疑惑.
 *
 * 一个例子,貌似是面试题.
 * 我第一次看到,相当然的认为在调用  test() 以后,
 * t 变成了一个野指针,但实际运行后发现, test() 调用中并没能改为实参 t 本身的值.
 * 充分说明了, c 语言的函数调用只有传值,没有传引用的说法.
 * 所谓的传引用,实际是传了一个指针进去,而指针变量本身也个内存的容器,
 * 它里面的值是另外一个内存容器(即变量)的地址值,
 * 在函数体中,通过取一级 * 运算,可以使用在函数中操作函数外的内存空间;
 * 但是,由于函数调用时会为每个参数在栈上开辟空间,换句话说,
 * 每个实际参数在进入函数调用的时候,都会使用一份拷贝(通常大的数组会传地址值进去,否则需要大内存来拷贝一份大数组),
 * 函数调用结束后,并不能改变实参本身的值,
 * 因为作用域,函数体内的局部变量在函数执行完后,全部自动销毁了,
 * 不能影响实参.
 *
 * 结合本例子,实参 t 在进入 test(int *p) 时,与形参 p 对应,
 * 系统会在栈为开辟内存空间,将 t 的内容拷贝到 p 中,
 * p 是 t 在函数栈空间上的一份拷贝,
 * 所以在在试图改变 p 的值,函数体外的 t 不会受到影响,
 * 因为 p = &tmp; 只是修改了栈上的复制版本.
 * 函数调用结束后,栈上的变量全部释放, t 的值保持原样.
 * */

void test(int *p)
{
    int tmp = 555;
    
    p = &tmp;
    return;
}

int main(int argc, char *argv[])
{
    int  a = 123;
    int *t = &a;

    test(t);

    printf(" a = %d\n", a);
    printf("*t = %d\n", *t);

    return 0;
}

