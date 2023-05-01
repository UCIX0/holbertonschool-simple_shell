
#include "main.h"
/**
 * check_arguments_and_terminal - Comprueba los argumentos y el terminal
 * @argc: número de argumentos proporcionados en la línea de comandos
 * @argv: array de cadenas que contiene los argumentos de la línea de comandos
 *
 * Esta función comprueba los argumentos proporcionados
 * en la línea de comandos y verifica si la entrada estándar
 * está conectada a un terminal o no.
 * Si no se proporcionan argumentos
 * y la entrada estándar está conectada a un terminal,
 * devuelve 1. Si se proporciona un argumento y este corresponde a un archivo
 * existente, devuelve 0. Si el argumento proporcionado no corresponde a un
 * archivo existente, muestra un mensaje de error y devuelve -1.
 * Es usada esta función para determinar si el programa sera interactivo o no.
 *
 * Return: 1 si no hay argumentos y la entrada estándar está conectada a un
 * terminal, 0 si se proporciona un argumento válido o -1 si el argumento
 * proporcionado es inválido y 2 si se usa tuberia.
 */
int check_arguments_and_terminal(int argc, char **argv)
{
	struct stat buffer;

	if (argc == 1)
	{
		if (isatty(STDIN_FILENO))
		{
			return (1);
		}
		return (2);
	}

	if (stat(argv[1], &buffer) == 0)
	{
		return (0);
	}
	fprintf(stderr, "%s: 1: %s: not found\n", argv[0], argv[1]);
	return (-1);
}
