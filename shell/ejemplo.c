#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Proceso hijo
        char *args[] = {"pwd", "-l", "-a", NULL};
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // Proceso padre
        int status;
        pid_t wait_pid = waitpid(pid, &status, 0);
        if (wait_pid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status)) {
            printf("El proceso hijo con PID %d terminó con estado de salida %d\n", pid, WEXITSTATUS(status));
        } else {
            printf("El proceso hijo con PID %d terminó de manera anormal\n", pid);
        }
    }
    return 0;
}
