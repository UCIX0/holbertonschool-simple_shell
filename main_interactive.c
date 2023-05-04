#include "main.h"

/**
 * procescmmd - procesa comandos según los delimitadores
 * @commandunit: estructura que contiene comandos y delimitadores
 * @paths: arreglo de rutas de directorios en la variable de entorno PATH
 */
void procescmmd(TokenizedInputPIPE *commandunit, char **paths)
{
	int status;
	int i = 0;

	do {
		if (i == 0 || commandunit->delimiters[i - 1][0] == ';')
		{
			status = execute(commandunit->commands[i], paths, 0, NULL);
		}
		else if (commandunit->delimiters[i - 1][0] == '|' && status != 0)
		{
			status = execute(commandunit->commands[i], paths, 0, NULL);
		}
		else if (commandunit->delimiters[i - 1][0] == '&' && status == 0)
		{
			status = execute(commandunit->commands[i], paths, 0, NULL);
		}
		i++;
	} while (i < commandunit->num_delimiters + 1);
}
/**
 * prepare_and_process_input - prepara el entorno y procesa
 * los comandos de entrada
 * @input: línea de entrada con comandos y delimitadores
 */
void prepare_and_process_input(char *input)
{
	TokenizedInputPIPE commandunit;
	char **env_copy = get_environment_copy();
	char *path_value;
	char **paths;
	char **exit_cmmd;

	path_value = get_path_variable(env_copy);
	paths = tokenize_path(path_value);
	commandunit = tokenize_inputpipe(input);
	exit_cmmd = tokenize_string(commandunit.commands[0]);
	if (strcmp(exit_cmmd[0], "exit") == 0)
	{
		if (exit_cmmd[1] == NULL)
		{
			free_tokenized_input_pipe(&commandunit);
			free_double_pointer(env_copy, count_elements(env_copy));
			free_double_pointer(paths, count_elements(paths));
			free(input);
			exit(0);
		}
			free_tokenized_input_pipe(&commandunit);
			free_double_pointer(env_copy, count_elements(env_copy));
			free_double_pointer(paths, count_elements(paths));
			free(input);
			exit(atoi(exit_cmmd[1]));
	}
	procescmmd(&commandunit, paths);

	free_tokenized_input_pipe(&commandunit);
	free_double_pointer(env_copy, count_elements(env_copy));
	free_double_pointer(paths, count_elements(paths));
}
/**
 * main_interactive - función principal que maneja el bucle interactivo
 *
 * Return: 0 si la ejecución fue exitosa
 */
int main_interactive(void)
{
	char *input;

	setup_signal_handlers();
	while (1)
	{
		char **exitmd;
		int ex;

		print_prompt();
		input = read_input();
		exitmd = tokenize_string(input);
		if (strcmp(exitmd[0], "exit") == 0)
		{
			if (exitmd[1] == NULL)
			{
				free_double_pointer(exitmd, count_elements(exitmd));
				free(input);
				exit(EXIT_SUCCESS);
			}
			ex = atoi(exitmd[1]);
			free_double_pointer(exitmd, count_elements(exitmd));
			free(input);
			exit(ex);
		}
		if (!input)
		{
			exit(EXIT_SUCCESS);
		}
		remove_comments(input);
		if (input[0] != '\0')
		{
			prepare_and_process_input(input);
		}
		free_double_pointer(exitmd, count_elements(exitmd));
		free(input);
	}
	return (0);
}
