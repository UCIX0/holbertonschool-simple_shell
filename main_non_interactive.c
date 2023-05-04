#include "main.h"

/**
 * proces_cmmd_noi - procesa comandos en modo no interactivo
 * @commandunit: estructura que contiene comandos y delimitadores
 * @paths: arreglo de rutas de directorios en la variable de entorno PATH
 * @arg0: nombre de la shell, usado para imprimir el error
 */
void proces_cmmd_noi(TokenizedInputPIPE *commandunit, char **paths, char *arg0)
{
	int status;
	int i = 0;

	do {
		if (i == 0 || commandunit->delimiters[i - 1][0] == ';')
		{
			status = execute(commandunit->commands[i], paths, 1, arg0);
		}
		else if (commandunit->delimiters[i - 1][0] == '|' && status != 0)
		{
			status = execute(commandunit->commands[i], paths, 1, arg0);
		}
		else if (commandunit->delimiters[i - 1][0] == '&' && status == 0)
		{
			status = execute(commandunit->commands[i], paths, 1, arg0);
		}
		i++;
	} while (i < commandunit->num_delimiters + 1);
}

/**
 * prepare_process_input_noi - prepara y procesa la entrada en no interactivo
 * @input: línea de entrada con comandos y delimitadores
 * @paths: arreglo de rutas de directorios en la variable de entorno PATH
 * @arg0: nombre de la shell, usado para imprimir el error
 */
void prepare_process_input_noi(char *input, char **paths, char *arg0)
{
	TokenizedInputPIPE commandunit;
	char **exit_cmmd;

	remove_comments(input);
	if (input[0] == '\0')
	{
		free(input);
		return;
	}
	commandunit = tokenize_inputpipe(input);
	exit_cmmd = tokenize_string(commandunit.commands[0]);
	if (strcmp(exit_cmmd[0], "exit") == 0)
	{
		if (exit_cmmd[1] == NULL)
		{
			free_tokenized_input_pipe(&commandunit);
			free(input);
			exit(0);
		}
				free_tokenized_input_pipe(&commandunit);
				free(input);
				exit(atoi(exit_cmmd[1]));
	}

	proces_cmmd_noi(&commandunit, paths, arg0);

	free_tokenized_input_pipe(&commandunit);
	free(input);
}

/**
 * main_non_interactive - función principal que maneja el modo no interactivo
 * @arg0: nombre de la shell, usado para imprimir el error
 * Return: 0 si la ejecución fue exitosa
 */
int main_non_interactive(char *arg0)
{
	char *input, *path_value;
	char **env_copy = get_environment_copy();
	char **paths, **exitmd;
	int ex;

	path_value = get_path_variable(env_copy);
	paths = tokenize_path(path_value);

	while ((input = read_input()) != NULL)
	{
		exitmd = tokenize_string(input);
		if (strcmp(exitmd[0], "exit") == 0)
		{
			if (exitmd[1] == NULL)
			{
				free_double_pointer(env_copy, count_elements(env_copy));
				free_double_pointer(paths, count_elements(paths));
				free(input);
				free_double_pointer(exitmd, count_elements(exitmd));
				exit(EXIT_SUCCESS);
			}
			ex = atoi(exitmd[1]);
			free_double_pointer(env_copy, count_elements(env_copy));
			free_double_pointer(paths, count_elements(paths));
			free_double_pointer(exitmd, count_elements(exitmd));
			free(input);
			exit(ex);
		}
		if (input[0] != '\0')
		{
			prepare_process_input_noi(input, paths, arg0);
		}
		else
		{
			free(input);
		}
	}
	free_double_pointer(env_copy, count_elements(env_copy));
	free_double_pointer(paths, count_elements(paths));
	return (0);
}
