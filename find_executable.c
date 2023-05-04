#include "main.h"



/**
 * try_direct_cmd - busca y ejecuta un comando directo (con '/')
 * y maneja errores
 * @cmd: comando a ejecutar
 * @full_path: buffer para almacenar la ruta completa del ejecutable
 * @mode: 0 si es interactivo, 1 si es no interactivo
 * @arg0: nombre de la shell, usado para imprimir errores
 *
 * Return: puntero al buffer 'full_path' si encuentra el ejecutable,
 * NULL en caso contrario.
 */
char *try_direct_cmd(const char *cmd, char *full_path, int mode, char *arg0)
{
	struct stat buffer;

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
	return (NULL);
}

/**
 * find_executable_path - busca un ejecutable en los directorios del PATH
 * @cmd: comando a buscar
 * @path_dirs: arreglo de directorios en la variable de entorno PATH
 * @full_path: buffer para almacenar la ruta completa del ejecutable
 *
 * Return: puntero al buffer 'full_path' si encuentra el ejecutable,
 * NULL en caso contrario.
 */

char *find_executable_path(const char *cmd, char **path_dirs, char *full_path)
{
	struct stat buffer;
	int i;

	for (i = 0; path_dirs[i] != NULL; i++)
	{
		snprintf(full_path, PATH_MAX, "%s/%s", path_dirs[i], cmd);
		if (stat(full_path, &buffer) == 0 && (buffer.st_mode & S_IXUSR))
		{
			return (full_path);
		}
	}
	return (NULL);
}

/**
 * find_executable - función principal que busca ejecutables usando las dos
 * funciones anteriores
 * @cmd: comando a buscar
 * @path_dirs: arreglo de directorios en la variable de entorno PATH
 * @mode: 0 si es interactivo, 1 si es no interactivo
 * @arg0: nombre de la shell, usado para imprimir errores
 *
 * Return: puntero a la ruta completa del ejecutable si se encuentra,
 * NULL en caso contrario.
 */
char *find_executable(const char *cmd, char **path_dirs, int mode, char *arg0)
{
	char *full_path = (char *)malloc(PATH_MAX);

	if (full_path == NULL)
	{
		fprintf(stderr, "memory allocation error\n");
		return (NULL);
	}

	if (strchr(cmd, '/'))
	{
		char *result = try_direct_cmd(cmd, full_path, mode, arg0);

		if (result)
		{
			return (full_path);
		}
	}
	else
	{
		char *result = find_executable_path(cmd, path_dirs, full_path);

		if (result)
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
