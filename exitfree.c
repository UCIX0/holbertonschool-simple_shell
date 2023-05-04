#include "main.h"
/**
 * free_tokenized_input_pipe - libera la memoria asignada a una estructura
 * TokenizedInputPIPE
 * @input: puntero a la estructura TokenizedInputPIPE
 *
 * La función libera la memoria asignada a los arreglos 'commands' y
 * 'delimiters' y sus elementos dentro de la estructura TokenizedInputPIPE.
 */
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
/**
 * free_double_pointer - libera la memoria asignada a un arreglo de punteros
 * @ptr: puntero al arreglo de punteros
 * @count: número de elementos en el arreglo
 *
 * La función libera la memoria asignada a los elementos del arreglo y al
 * arreglo en sí mismo.
 */
void free_double_pointer(char **ptr, int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		free(ptr[i]);
	}
	free(ptr);
}
