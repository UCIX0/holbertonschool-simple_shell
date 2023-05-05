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
int main(int argc, char **arg)
{
	int interactiveorno;

	argc++;
	interactiveorno = check_arguments_and_terminal();
	if (interactiveorno == 0)
	{
		main_interactive();
	} else if (interactiveorno == 1)
	{
		main_non_interactive(arg[0]);
	}
	else
	{
		printf("Error\n");
	}
	return (0);
}
