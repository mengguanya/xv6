#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAXN 1024

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(2, "usage: xargs command\n");
        exit(1);
    }
    /* 存放子进程exec的参数 */
    char *_argv[MAXARG];
    /* 存放子进程exec参数的个数 */
    int _argc;

    /* 省略xargs */
    for (int i = 1; i < argc; i++)
    {
        _argv[i - 1] = argv[i];
    }

    /* 存放从标准输入转化来的参数 */
    char buf[MAXN];

    char c = 0;

    /* 从标准输入read返回的状态 */
    int stat;

    while (stat)
    {
        _argc = argc - 1;
        /* 当前这个参数在buffer的开头 */
        int arg_begin = 0;
        /* 当前这个参数在buffer的结尾 */
        int arg_end = 0;
        /* 读取一行参数，然后执行子程序 */
        while (1)
        {
            /* 从标准输入read返回的状态 */
            stat = read(0, &c, 1);
            if (stat == 0)
                exit(0);
            
            /* xargs为子进程传递参数，以空格分隔 */
            if(c == ' ' || c == '\n'){
                buf[arg_end++] = 0;
                _argv[_argc++] = &buf[arg_begin];
                arg_begin = arg_end;
                /* xargs为子进程传递参数以换行为结束 */
                if(c == '\n'){
                    break;
                }
            }
            else{
                buf[arg_end++] = c;
            }
        }
        
        _argv[_argc] = 0;

        if(fork() == 0){
            exec(_argv[0], _argv);
        }
        else{
            wait(0);
        }
    }
    exit(0);
}