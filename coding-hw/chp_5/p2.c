#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main() {
    int fd = open("./p2-output.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (fd < 0) {
        fprintf(stderr, "file open failed\n");
        exit(1);
    }

    close(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);

    printf("Parent Process (pid:%d)\n", (int)getpid());

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("child (pid:%d)\n", (int)getpid());
        printf("file descriptor from child: %d\n", fd);
        const char *child_msg = "Child says 'Hi, Papa2'\n";
        write(fd, child_msg, strlen(child_msg));
    }
    else
    {
        //parent path
        int rc_wait = wait(NULL);
        printf("parent of %d (pid:%d)\n", rc, (int)getpid());
        printf("file descriptor from parent: %d\n", fd);
        const char *parent_msg = "Parent says 'Hi, Kiddo'\n";
            write(fd, parent_msg, strlen(parent_msg));
        
    }

    close(fd);
    return 0;
}