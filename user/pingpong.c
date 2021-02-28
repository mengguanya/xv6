#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "./user.h"

int main(int argc, char *argv[])
{
    char c = 'a';
    int n;
    int to_child[2],
        from_child[2];

    pipe(to_child);
    pipe(from_child);

    /* 父进程 */
    if (!fork())
    {
        close(to_child[0]);
        close(from_child[1]);

        write(to_child[1], &c, 1);

        n = read(from_child[0], &c, 1);
        if(n != 1){
            fprintf(2, "parent read error\n");
            exit(1);
        }

        printf("%d: received pong\n", getpid());

        close(to_child[1]);
        close(from_child[0]);

        wait(0);
        exit(0);
    }
    /* 子进程 */
    else
    {
        close(to_child[1]);
        close(from_child[0]);

        n = read(to_child[0], &c, 1);

        if (n != 1)
        {
            fprintf(2, "child read error\n");
            exit(1);
        }

        printf("%d: received ping\n", getpid());

        write(from_child[1], &c, 1);

        close(to_child[0]);
        close(from_child[1]);

        exit(0);
    }
    return 0;
}