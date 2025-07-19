#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main() {
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed");
        exit(1);
    } else if (rc == 0) {
        int status = wait(NULL);
        printf("I'm the child %d\n", (int)getpid());
        printf("wait returned: %d\n", status);
    }
    else
    {
        int status = wait(NULL);
        printf("parent here again pid:%d\n Wait returned: %d", (int)getpid(), status);
    }
}