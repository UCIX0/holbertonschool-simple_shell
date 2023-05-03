#include "main.h"

void free_tokenized_input_pipe(TokenizedInputPIPE *input)
{
	int i;

	for (i = 0; i < input->num_commands; i++)
	{
		free(input->commands[i]);
	}
	free(input->commands);

	for (i = 0; i < input->num_delimiters; i++)
	{
		free(input->delimiters[i]);
	}
	free(input->delimiters);
}

void free_double_pointer(char **ptr, int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		free(ptr[i]);
	}
	free(ptr);
}

void myexit(int extnum)
{
	exit(extnum);
}
