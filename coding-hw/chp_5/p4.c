#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main() {
    printf("hello process pid:%d\n", (int)getpid());

    int pipefd[2];
    char buffer[1];

    if (pipe(pipefd) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("Child process pid:%d\n", (int)getpid());

        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);

        execl("/bin/ls", "ls", (char *)NULL);
        perror("execl failed");
        exit(1);
    } else {
        close(pipefd[1]);

        char buffer[1024];
        ssize_t n;

        while((n = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[n] = '\0';
            printf("%s", buffer); // Print output as it comes in
        }

        close(pipefd[0]);
        wait(NULL);
    }

     return 0;
}