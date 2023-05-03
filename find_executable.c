#include "main.h"

/**
 * find_executable - Busca un archivo ejecutable en
 * los directorios de la variable PATH
 * @cmd: puntero a la cadena de caracteres
 * que contiene el nombre del comando
 * @path_dirs: puntero al arreglo de cadenas
 * que contiene los directorios de la variable PATH
 *
 * Esta función busca un archivo ejecutable en los directorios de la variable
 * PATH. Si el nombre del comando contiene un '/', se verifica si el archivo
 * existe y es ejecutable. Si no contiene un '/', se busca en los directorios
 * de la variable PATH. Si se encuentra el archivo ejecutable, se devuelve la
 * ruta del archivo ejecutable. En caso contrario, se imprime un mensaje de
 * error y se devuelve NULL.
 *
 * Return: ruta del archivo ejecutable si se encuentra, NULL en caso contrario
 */
char *find_executable(const char *cmd, char **path_dirs, int mode, char *arg0)
{
	struct stat buffer;
	char *full_path = (char *)malloc(PATH_MAX);
	int i;

	if (full_path == NULL)
	{
		fprintf(stderr, "memory allocation error\n");
		return (NULL);
	}

	if (strchr(cmd, '/'))
	{
		strncpy(full_path, cmd, PATH_MAX - 1);
		full_path[PATH_MAX - 1] = '\0';
		if (stat(full_path, &buffer) == 0 && (buffer.st_mode & S_IXUSR))
		{
			return (full_path);
		}
		if (mode == 0)
		{
			fprintf(stderr, "no such file or directory: %s\n", full_path);
		}
		else
		{
			fprintf(stderr, "%s: 1: %s: not found\n", arg0, cmd);
		}
		free(full_path);
		return (NULL);
	}

	for (i = 0; path_dirs[i] != NULL; i++)
	{
		snprintf(full_path, PATH_MAX, "%s/%s", path_dirs[i], cmd);
		if (stat(full_path, &buffer) == 0 && (buffer.st_mode & S_IXUSR))
		{
			return (full_path);
		}
	}

	if (mode == 0)
	{
		fprintf(stderr, "command not found: %s\n", cmd);
	}
	else
	{
		fprintf(stderr, "%s: 1: %s: not found\n", arg0, cmd);
	}
	free(full_path);
	return (NULL);
}
