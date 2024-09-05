#include "shell.h"

/**
 * clear_info - initializes shell_info struct
 * @info: struct address
 */
void clear_info(shell_info *info)
{
	info->input_line = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes shell_info struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(shell_info *info, char **av)
{
	int i = 0;

	info->program_name = av[0];
	if (info->input_line)
	{
		info->argv = strtow(info->input_line, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->input_line);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - frees shell_info struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(shell_info *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_chain_buf)
			free(info->input_line);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->custom_environ);
			info->custom_environ = NULL;
		bfree((void **)info->cmd_chain_buf);
		if (info->input_fd > 2)
			close(info->input_fd);
		_putchar(BUF_FLUSH);
	}
}
