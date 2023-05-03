#include "main.h"

int main_interactive(void)
{
	char *input;

	setup_signal_handlers();
	while (1)
	{
		print_prompt();
		input = read_input();
		if (!input)
		{
			exit(EXIT_SUCCESS);
		}
		remove_comments(input);
		if (input[0] != '\0')
		{
			TokenizedInputPIPE commandunit;
			char **env_copy = get_environment_copy();
			char *path_value;
			char **paths;
			int status;
			int i = 0;

			path_value = get_path_variable(env_copy);
			paths = tokenize_path(path_value);
			commandunit = tokenize_inputpipe(input);

			do {
				if (i == 0 || commandunit.delimiters[i - 1][0] == ';')
				{
					status = execute(commandunit.commands[i], paths, 0, NULL);
				}
				else if (commandunit.delimiters[i - 1][0] == '|' && status != 0)
				{
					status = execute(commandunit.commands[i], paths, 0, NULL);
				}
				else if (commandunit.delimiters[i - 1][0] == '&' && status == 0)
				{
					status = execute(commandunit.commands[i], paths, 0, NULL);
				}
				i++;
			} while (i < commandunit.num_delimiters + 1);
			free_tokenized_input_pipe(&commandunit);
			free_double_pointer(env_copy, count_elements(env_copy));
			free_double_pointer(paths, count_elements(paths));
		}
		free(input);
	}
	return (0);
}
