#include "main.h"
/**
 * count_paths - Cuenta la cantidad de rutas en el valor de PATH
 * Esta función cuenta la cantidad de rutas en la cadena de PATH,
 * identificando las rutas separadas por el carácter ':'.
 * @path_value: puntero a la cadena de caracteres que contiene el valor de PATH
 * Return: La cantidad de rutas en el valor de PATH
 */
size_t count_paths(const char *path_value)
{
	size_t path_count = 1;
	const char *p;

	for (p = path_value; *p != '\0'; p++)
	{
		if (*p == ':')
		{
			path_count++;
		}
	}
	return (path_count);
}
/**
 * copy_paths - Copia las rutas individuales del valor de PATH a un arreglo
 * @paths: puntero al arreglo de cadenas que contendrá las rutas individuales
 * @path_value: puntero a la cadena de caracteres que contiene el valor de PATH
 */
void copy_paths(char **paths, const char *path_value)
{
	const char *p;
	const char *start = path_value;
	size_t path_index = 0;

	for (p = path_value; ; p++)
	{
		if (*p == ':' || *p == '\0')
		{
			size_t len = p - start;

			paths[path_index] = (char *)malloc(len + 1);
			if (!paths[path_index])
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			strncpy(paths[path_index], start, len);
			paths[path_index][len] = '\0';
			path_index++;
			start = p + 1;
		}
		if (*p == '\0')
		{
			break;
		}
	}
}
/**
 * tokenize_path - Divide la variable PATH en un arreglo de rutas
 * @path_value: puntero a la cadena de caracteres que contiene el valor de PATH
 * Esta función divide la cadena de caracteres que contiene el valor de PATH
 * en un arreglo de rutas, separadas por el carácter ':'.
 * Return: Un puntero al arreglo de cadenas que contiene las rutas individuales
 */
char **tokenize_path(const char *path_value)
{
	size_t path_count = count_paths(path_value);
	char **paths = (char **)malloc((path_count + 1) * sizeof(char *));

	if (!paths)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	copy_paths(paths, path_value);
	paths[path_count] = NULL;

	return (paths);
}
