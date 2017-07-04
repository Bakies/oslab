#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFER_SIZE 128
#define READ_END 0
#define WRITE_END 1

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
        /* write to the pipe */
        write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
        printf("P wrote %s\n",write_msg);
        /* close the write end of the pipe */
        close(fd[WRITE_END]);
	read(fd[READ_END], write_msg, strlen(read_msg) + 1);
	printf("P read %s\n", write_msg);
    }
    else { /* child process */
        /* read from the pipe */
        read(fd[READ_END], read_msg, BUFFER_SIZE); 
	printf("C read %s\n",read_msg);
        /* close the write end of the pipe */
        close(fd[READ_END]);
	switchCase(read_msg);
	write(fd[WRITE_END], read_msg, strlen(read_msg) + 1);
	printf("C wrote %s\n", read_msg);
        close(fd[WRITE_END]);
    }
    return 0;
}
