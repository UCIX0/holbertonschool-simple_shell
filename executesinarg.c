#include "main.h"

int execute_command_args(const char *command_line)
{
	char *command, *save_ptr, *token;
	char **argv = NULL;
	int argc = 0, status;
	pid_t pid;

	command = strdup(command_line);
	if (!command)
	{
		perror("strdup");
		return (-1);
	}

	token = strtok_r(command, " ", &save_ptr);
	while (token)
	{
		argv = realloc(argv, (argc + 1) * sizeof(char *));
		argv[argc++] = token;
		token = strtok_r(NULL, " ", &save_ptr);
	}
	argv = realloc(argv, (argc + 1) * sizeof(char *));
	argv[argc] = NULL;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(command);
		free(argv);
		return (-1);
	} else if (pid == 0)
	{
		execvp(argv[0], argv);
		perror("execvp");
		exit(EXIT_FAILURE);
	} else
	{
		if (waitpid(pid, &status, 0) < 0)
		{
			perror("waitpid");
			free(command);
			free(argv);
			return (-1);
		}
	}

	if (WIFEXITED(status) == 1)
	{
		return (WEXITSTATUS(status));
	}

	free(command);
	free(argv);
	return (0);
}
