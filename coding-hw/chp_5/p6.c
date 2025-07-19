#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main() {
    pid_t rc = fork();
    printf("%d\n", rc);

    if (rc < 0) {
        fprintf(stderr, "fork failed");
        exit(1);
    } else if (rc == 0) {
        printf("I'm the child %d\n", (int)getpid());
    }
    else
    {
        int status = waitpid(rc, NULL, 0);
        printf("parent here again pid:%d\n Wait returned: %d\n", (int)getpid(), status);
    }
}