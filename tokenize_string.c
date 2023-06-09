#include "main.h"
/**
 * count_elements - cuenta el número de elementos en un array de punteros
 * @ptr: array de punteros
 * Return: número de elementos en el array
 */
int count_elements(char **ptr)
{
	int count = 0;

	while (*ptr != NULL)
	{
		count++;
		ptr++;
	}
	return (count);
}

/**
 * resize_tokens_array - redimensiona un array de tokens
 * @tokens: doble puntero al array de tokens
 * @tokens_size: puntero al tamaño actual del array
 */
void resize_tokens_array(char ***tokens, size_t *tokens_size)
{
	*tokens_size *= 2;
	*tokens = (char **)realloc(*tokens, *tokens_size * sizeof(char *));
	if (!*tokens)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
}
/**
 * tokenize_string - tokeniza una cadena basándose en espacios
 * @input: cadena de entrada
 * Return: array de tokens
 */
char **tokenize_string(const char *input)
{
	size_t tokens_size = 16;
	size_t tokens_count = 0;
	char *input_copy;
	char *token;
	char **tokens = (char **)malloc(tokens_size * sizeof(char *));

	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	input_copy = strdup(input);
	if (!input_copy)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}

	token = strtok(input_copy, " ");
	while (token)
	{
		if (tokens_count >= tokens_size)
		{
			resize_tokens_array(&tokens, &tokens_size);
		}

		tokens[tokens_count] = strdup(token);
		tokens_count++;
		token = strtok(NULL, " ");
	}

	free(input_copy);

	tokens[tokens_count] = NULL;
	return (tokens);
}
