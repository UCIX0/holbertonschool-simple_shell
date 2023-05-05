#include "main.h"
/**
 * check_arguments_and_terminal - verifica si esta en interactiva o no
 * Return: 0 si es interactivo, 1 si es no interactivo, -1 si hay un error
 */
int check_arguments_and_terminal(void)
{
		if (isatty(STDIN_FILENO))
		{
			return (0);
		}
		return (1);
	return (-1);
}
/**
 * main - función principal del programa
 * @argc: número de argumentos
 * @arg: arreglo de argumentos
 * Return: 0 si la ejecución fue exitosa
 */
#include "main.h"
/**
 * main - funcion principal
 * Return: 0
 */
int main(void)
{
	char *prog[] = {"bin/ls", "-l", NULL};

	execve("bin/ls", prog, NULL);
	return (0);
}
