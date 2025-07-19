#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("hello (pid: %d)\n", (int)getpid());
    int x;
    x = 100;

    int rc = fork();
    if (rc < 0)
    {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child (new process)
        x = 50;
        printf("child (pid:%d)\n", (int)getpid());
        printf("variable 'x' in child: %d\n", x);
    }
    else {
        // parent path
        int rc_wait = wait(NULL);
        printf("parent of %d (pid:%d)\n", rc, (int)getpid());
        printf("variable 'x' in parent: %d\n", x);
    }

    return 0;
}