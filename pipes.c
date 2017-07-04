#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFER_SIZE 25
#define READ_END1 0
#define WRITE_END1 1
#define READ_END2 2
#define WRITE_END2 3

void switchCase(char *buffer) {
    for (int i = 0; i < strlen(buffer); i++) {
        if (isupper(buffer[i])) {
            buffer[i] = tolower(buffer[i]);
        }
        else if (islower(buffer[i])) {
            buffer[i] = toupper(buffer[i]);
        }
    }
}

int main(void) {
    char write_msg[BUFFER_SIZE] = "Hi There";
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;
    /* create the pipe */
    if (pipe(fd) == -1) {
        fprintf(stderr,"Pipe failed");
        return 1;
    }
    /* fork a child process */
    pid = fork();
    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    if (pid > 0) { /* parent process */
        /* close the unused end of the pipe */
        close(fd[READ_END1]);
        /* write to the pipe */
        write(fd[WRITE_END1], write_msg, strlen(write_msg)+1);
        switchCase(write_msg);
        printf("write %s",write_msg);
        /* close the write end of the pipe */
        close(fd[WRITE_END1]);
        }
    else { /* child process */
        /* close the unused end of the pipe */
        close(fd[WRITE_END1]);
        /* read from the pipe */
        read(fd[READ_END1], read_msg, BUFFER_SIZE); printf("read %s",read_msg);
        /* close the write end of the pipe */
        close(fd[READ_END1]);
        }
    return 0;
}