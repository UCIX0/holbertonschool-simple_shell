#include "main.h"
/**
 * execve_builtin - ejecuta comandos incorporados si están presentes
 * @cmmdunittokens: tokens de la unidad de comando
 * Return: 0 si el comando incorporado se ejecutó con éxito,
 * -1 si no se encontróningún comando incorporado
 */
int execve_builtin(char **cmmdunittokens)
{
	if (cmmdunittokens[0] == NULL)
	{
		return (-1);
	}
	if (strcmp(cmmdunittokens[0], "cd") == 0)
	{
		if (!cmmdunittokens[2])
		{
			my_cd(cmmdunittokens[1]);
			return (0);
		}
		fprintf(stderr, "Error cd necesita más vatiablers\n");
	}
		if (strcmp(cmmdunittokens[0], "env") == 0)
	{
		print_environment();
		return (0);
	}
	if (strcmp(cmmdunittokens[0], "setenv") == 0)
	{
		if (cmmdunittokens[1] && cmmdunittokens[2])
		{
			my_setenv(&environ, cmmdunittokens[1], cmmdunittokens[2]);
			return (0);
		}
		fprintf(stderr, "Error Setenv necesita más vatiablers\n");
		return (0);
	}
	if (strcmp(cmmdunittokens[0], "unsetenv") == 0)
	{
		if (cmmdunittokens[1] && !cmmdunittokens[2])
		{
			my_unsetenv(&environ, cmmdunittokens[1]);
			return (0);
		}
		fprintf(stderr, "Error unsetenv necesita más vatiablers\n");
		return (0);
	}
	return (-1);
}

/**
 * my_cd - cambia el directorio actual al directorio
 * especificado por 'path'
 * @path: la ruta del directorio al que se cambiará
 * Return: 0 si se cambia el directorio con éxito,
 * -1 en caso de error
 */

int my_cd(const char *path)
{
	if (path == NULL)
	{
		perror("my_cd: NULL path");
		return (-1);
	}

	if (chdir(path) != 0)
	{
		fprintf(stderr, "my_cd: %s: %s\n", path, strerror(errno));
		return (-1);
	}

	return (0);
}
