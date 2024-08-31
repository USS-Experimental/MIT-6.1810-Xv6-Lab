#include "kernel/types.h"
#include "user/user.h"

int main()
{
    int p[2];
    char buffer[16];
    pipe(p);

    int pid = fork();
    if (pid == -1)
    {
        fprintf(2, "fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        read(p[0], buffer, 16);
        close(p[0]);

        printf("%d: received ping\n", getpid());

        write(p[1], buffer, sizeof(buffer));
        close(p[1]);

        return 0;
    }
    else
    {
        write(p[1], "114514\n", 7);
        close(p[1]);

        read(p[0], buffer, 16);
        close(p[0]);

        printf("%d: received pong\n", getpid());

        return 0;
    }    
    
}