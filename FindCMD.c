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
 * de la variable PATH. Si se encuentra el archivo ejecutable, se devuelve 0.
 * En caso contrario, se imprime un mensaje de error y se devuelve -1.
 *
 * Return: 0 si se encuentra el archivo ejecutable, -1 en caso contrario
 */
int find_executable(const char *cmd, char **path_dirs)
{
	struct stat buffer;
	char full_path[PATH_MAX];
	int i;

	if (strchr(cmd, '/'))
	{
		if (stat(cmd, &buffer) == 0 && (buffer.st_mode & S_IXUSR))
		{
			return (0);
		}
		fprintf(stderr, "no such file or directory: %s\n", cmd);
		return (-1);
	}

	for (i = 0; path_dirs[i] != NULL; i++)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", path_dirs[i], cmd);
		if (stat(full_path, &buffer) == 0 && (buffer.st_mode & S_IXUSR))
		{
			return (0);
		}
	}

	fprintf(stderr, "command not found: %s\n", cmd);
	return (-1);
}
