#include "main.h"
/**
 * print_prompt - Imprime el símbolo del sistema en la consola
 *
 * Esta función imprime el símbolo del sistema ($ ) en la consola y
 * vacía el búfer de salida para asegurar que se muestre.
 */
void print_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}
/**
 * read_input - Lee la entrada del usuario desde la consola
 *
 * Esta función lee la entrada del usuario desde la consola
 * y devuelve una cadena de caracteres que contiene la entrada leída.
 * Return: Un puntero a una cadena de caracteres con la entrada del usuario,
 * o NULL si no se pudo leer la entrada
 */

char *read_input()
{
	size_t buffer_size = BUFFER_SIZE;
	ssize_t getline_ret;
	char *buffer = (char *)malloc(buffer_size * sizeof(char));

	if (!buffer)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	memset(buffer, '\0', buffer_size);

	getline_ret = getline(&buffer, &buffer_size, stdin);

	if (getline_ret == -1)
	{
		free(buffer);
		return (NULL);
	}

	if (getline_ret > 0 && buffer[getline_ret - 1] == '\n')
	{
		buffer[getline_ret - 1] = '\0';
	}

	return (buffer);
}

/**
 * remove_comments - Elimina los comentarios de una cadena de entrada
 * @input: puntero a la cadena de caracteres que contiene la entrada
 *
 * Esta función busca el inicio de un comentario
 * (indicado por el carácter '#')
 * en la cadena de entrada y, si lo encuentra, lo elimina junto con todo lo
 * que sigue, modificando la cadena original.
 */
void remove_comments(char *input)
{
	char *comment_start;

	/* Buscar el inicio del comentario */
	comment_start = strchr(input, '#');

	/* Si se encuentra un comentario y hay un espacio antes del '#', reemplazar el primer caracter del comentario con '\0' */
	while (comment_start != NULL)
	{
		if (comment_start > input && *(comment_start - 1) == ' ')
		{
			*comment_start = '\0';
			break;
		}
		comment_start = strchr(comment_start + 1, '#');
	}
}

