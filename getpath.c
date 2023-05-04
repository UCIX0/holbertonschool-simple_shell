#include "main.h"

/**
 * get_path_variable - Obtiene la variable PATH del entorno
 * @env_copy: puntero al arreglo de cadenas que representa el entorno actual
 *
 * Esta función busca la variable PATH en el entorno proporcionado y devuelve
 * un puntero a su valor. Si la variable PATH no se encuentra, se devuelve un
 * valor predeterminado.
 *
 * Return: Un puntero a la cadena de caracteres que contiene el valor de la
 *         variable PATH, o un valor predeterminado si no se encuentra
 */
char *get_path_variable(char **env_copy)
{
	size_t i;

	for (i = 0; env_copy[i] != NULL; i++)
	{
		if (strncmp(env_copy[i], "PATH=", 5) == 0)
		{
			return (env_copy[i] + 5);
		}
	}
	return ("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
}
