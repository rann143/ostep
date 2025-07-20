#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main() {
    printf("Daddy says Hi\n");

    int pipefd[2];

    if (pipe(pipefd) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed");
        exit(1);
    } else if (rc == 0) {
        close(pipefd[0]);

        dup2(pipefd[1], STDOUT_FILENO);
        printf("Hello from child1, pid:%d\n", (int)getpid());
        exit(0);
    } else {
        printf("child1 completed\n");
    }

    int rc2 = fork();

    if (rc2 < 0) {
        fprintf(stderr, "fork failed");
        exit(1);
    } else if (rc2 == 0){
        printf("Hi, I'm child2 (pid:%d). Here's a message from child1:\n", (int)getpid());
        close(pipefd[1]);

        dup2(pipefd[0], STDIN_FILENO);

        char buffer[1024];

        while(fgets(buffer, sizeof(buffer), stdin) != NULL) {
            printf("  -> %s", buffer);
        }

        close(pipefd[0]);
        exit(0);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);

    printf("both children completed");

    return 0;
}