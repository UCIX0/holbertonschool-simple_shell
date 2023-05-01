#include "main.h"

int count_elements(char **ptr) {
    int count = 0;
    while (*ptr != NULL) {
        count++;
        ptr++;
    }
    return count;
}


int main_interactive(void)
{
	char *input;
	setup_signal_handlers();

	while (1) {
		TokenizedInputPIPE tokenized;
		char **tonez;
		int find;
		print_prompt();
		input = read_input();
		if (!input) {
			printf("saliendo\n");
			exit(EXIT_SUCCESS);
		}

		remove_comments(input);
		if (input[0] != '\0') {
			char **env_copy = get_environment_copy();
			char *path_value;
			char **paths;
			path_value = get_path_variable(env_copy);
			paths = tokenize_path(path_value);
			tokenized = tokenize_inputpipe(input);
			tonez = tokenizemin(tokenized.commands[0]);
			find = find_executable(tonez[0], paths);
			if (find == 0)
			{
				int numtok = count_elements(tonez);
				if (numtok == 1)
				{
					execute_program(tonez[0]);
				}
				else if (numtok > 1)
				{
					execute_command_args(input);
				}
			}
			free(tonez);
		}
	}

	return 0;
}