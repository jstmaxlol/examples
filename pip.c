/*
 *  PIP in C
 *  simple demonstration of a program in program.. program.
 *  czjstmax <jstmaxlol at disroot dot org>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed.");
        return 1;
    }

    if (pid == 0) {
        // After successfully creating a child,
        // replace it with another program, 
        // in this example we are using VIM.
        execlp("vim", "vim", NULL);

        // If execlp() returns, it failed.
        perror("execlp failed");
        exit(127);
    } else {
        // Here the parent process is waiting
        // for the child to finish execution.
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid failed");
            return 1;
        }

        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("VIM exited with code %d\n", exit_code);
            // Here the parent can continue execution.
        } else if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            printf("VIM was killed by signal %d\n", sig);
        } else {
            printf("VIM exited abnormally\n");
        }
    }

    // Here can go the rest of the program.
    printf("Back to main!\n");
    return 0;
}

