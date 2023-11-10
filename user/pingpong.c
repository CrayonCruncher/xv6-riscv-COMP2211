#include "kernel/types.h"
#include "user/user.h"

int main() {
    int p[2];
    char our_byte = 'P';

    pipe(p);
    int pid = fork();
    if (pid > 0) //parent
    {
        write(p[1], &our_byte, 1);
        pid = wait((int *) 0);
        char received_byte;
        read(p[0], &received_byte, 1);
        int mypid = get_pid();
        printf("%d:Received pong, %c\n", mypid, received_byte);
    }
    else if (pid == 0) //child
    {
        read(p[0], &our_byte, 1);
        mypid = get_pid();
        printf("%d:Received ping, %c\n", mypid, received_byte);
        if (received_byte == 'P')
        {
            received_byte = 'R';
        }
        write(p[1], received_byte, 1);
    }
    exit(0);