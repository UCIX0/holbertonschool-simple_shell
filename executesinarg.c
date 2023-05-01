#include "main.h"

int execute_program(char *program) {
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0) {
		perror("fork");
		return -1;
	} else if (pid == 0) {
		char *argv[2];
		argv[0] = program;
		argv[1] = NULL;
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
			return 127;
		}
	}
	return 0;
}
