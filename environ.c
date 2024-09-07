#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(shell_info *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_env_value - gets the value of an environ variable
 * @info_shell: Structure containing potential arguments. Used to maintain
 * @var_name: env var name
 *
 * Return: the value
 */
char *get_env_value(shell_info *info_shell, const char *var_name)
{
	list_node *env_node = info_shell->env;
	char *var_value;

	while (env_node)
	{
		var_value = find_substring(env_node->data, var_name);
		if (var_value && *var_value)
			return (var_value);
		env_node = env_node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(shell_info *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(shell_info *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info_shell: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(shell_info *info_shell)
{
	list_node *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info_shell->env = node;
	return (0);
}
