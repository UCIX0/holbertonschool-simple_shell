#include "main.h"

int execute (char *commandu, char **paths, int mode, char *arg0)
{
	char **cmmdunittokens;
	int status;
	char *command_path;
	int countelements;
	cmmdunittokens = tokenize_string(commandu);
	if (cmmdunittokens[0] == NULL)
	{
		free_double_pointer(cmmdunittokens, count_elements(cmmdunittokens));
		return -1;
	}
	command_path = find_executable(cmmdunittokens[0], paths, mode, arg0);
	countelements = count_elements(cmmdunittokens);
	if (command_path != NULL)
	{
		if (countelements == 1)
		{
			status = execve_without_arg(command_path);
		}
		else
		{
			status = execute_with_args(command_path, cmmdunittokens, countelements);
		}
	}
	free_double_pointer(cmmdunittokens, count_elements(cmmdunittokens));
	free(command_path);
	return status;
}

int execve_without_arg(const char *program) {
	pid_t pid;
	int status;
	pid = fork();
	if (pid < 0) {
		perror("fork");
		return -1;
	} else if (pid == 0) {
		char *argv[2];

		argv[0] = (char *) program;
		argv[1] = NULL;

		if (execve(program, argv, NULL) == -1) {
			perror("execve");
			exit(EXIT_FAILURE);
		}
	} else {
		if (waitpid(pid, &status, 0) < 0) {
			perror("waitpid");
			return -1;
		}
		if (WIFEXITED(status)) {
			return WEXITSTATUS(status);
		} else {
			fprintf(stderr, "Error: child process terminated abnormally.\n");
			return -1;
		}
	}
	return 0;
}

int execute_with_args(const char *path, char **args, int count)
{
	pid_t pid;
	int i;
	char **exec_args;
	int status;

	exec_args =  malloc((count + 1) * sizeof(char *));
	if (!exec_args)
	{
		perror("malloc");
		return -1;
	}

	exec_args[0] = (char *) path;
	for (i = 1; i < count; i++)
	{
		exec_args[i] = args[i];
	}
	exec_args[count] = NULL;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(exec_args);
		return -1;
	}
	else if (pid == 0)
	{
		if (execve(path, exec_args, NULL) < 0)
		{
			perror("execve");
			free(exec_args);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) < 0)
		{
			perror("waitpid");
			free(exec_args);
			return -1;
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
		{
			free(exec_args);
			return 0;
		}
		else
		{;
			free(exec_args);
			return WEXITSTATUS(status);
		}
	}
	return 0;
}
