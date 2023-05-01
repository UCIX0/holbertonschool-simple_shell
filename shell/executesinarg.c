#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int execute_program(char *program) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return -1;
    } else if (pid == 0) {
        char *argv[] = {program, NULL};
        if (execvp(argv[0], argv) < 0) {
            perror(program);
            exit(EXIT_FAILURE);
        }
    } else {
        if (waitpid(pid, &status, 0) < 0) {
            perror("waitpid");
            return -1;
        }
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            return 0;
        } else {
            return -1;
        }
    }
}

int main()
{
    int i = execute_program("caca");
    return 0;
}
