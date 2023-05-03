#include "main.h"

int main_non_interactive(char *arg0)
{
	char *input;
	TokenizedInputPIPE commandunit;
	char **env_copy = get_environment_copy();
	char *path_value;
	char **paths;
	int status;

	path_value = get_path_variable(env_copy);
	paths = tokenize_path(path_value);

	while ((input = read_input()) != NULL)
	{
		if (input[0] != '\0')
		{
			int i = 0;

			remove_comments(input);
			if (input[0] == '\0')
			{
				free(input);
				free_double_pointer(env_copy, count_elements(env_copy));
				free_double_pointer(paths, count_elements(paths));
				exit(EXIT_SUCCESS);
			}
			commandunit = tokenize_inputpipe(input);

			do {
				if (i == 0 || commandunit.delimiters[i - 1][0] == ';')
				{
					status = execute(commandunit.commands[i], paths, 1, arg0);
				}
				else if (commandunit.delimiters[i - 1][0] == '|' && status != 0)
				{
					status = execute(commandunit.commands[i], paths, 1, arg0);
				}
				else if (commandunit.delimiters[i - 1][0] == '&' && status == 0)
				{
					status = execute(commandunit.commands[i], paths, 1, arg0);
				}
				i++;
			} while (i < commandunit.num_delimiters + 1);

			free_tokenized_input_pipe(&commandunit);
		}

		free(input);
	}

	free_double_pointer(env_copy, count_elements(env_copy));
	free_double_pointer(paths, count_elements(paths));

	return (0);
}

