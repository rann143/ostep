#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main() {

    int pipefd[2];
    char buffer[1];

    if (pipe(pipefd) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

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
        close(pipefd[0]);

        printf("Hello\n");
        fflush(stdout);

        write(pipefd[1], "x", 1);
        close(pipefd[1]);

        exit(0);
    }
    else {
        // parent path

        close(pipefd[1]);
        read(pipefd[0], &buffer, 1);
        close(pipefd[0]);

        printf("GoodBye\n");
        printf("buffer: %c", buffer[0]);
    }

    return 0;
}