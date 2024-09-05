#include "shell.h"

/**
 * main - Punto de entrada
 * @argc: numero de argumentos
 * @argv: array con los input_line
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	shell_info info[] = { SHELL_INFO_INIT };
	int file_descriptor = STDIN_FILENO;

	if (argc == 2)
	{
		file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				fprintf(stderr, "%s: 0: Can't open %s\n", argv[0], argv[1]);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->input_fd = file_descriptor;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, argv);
	return (EXIT_SUCCESS);
}
