#include "main.h"
/**
 * get_environment_variable - Obtiene el valor
 * de una variable de entorno
 * @env_copy: puntero al arreglo de cadenas
 * que representa el entorno actual
 * @var: puntero a la cadena de caracteres
 * que contiene el nombre de la variable
 *
 * Esta función busca una variable de entorno
 * con el nombre especificado en el
 * entorno proporcionado y devuelve un puntero
 * a su valor. Si la variable no
 * se encuentra, devuelve NULL.
 *
 * Sintaxis del comando: $VARIABLE
 *
 * Return: Un puntero a la cadena de caracteres
 * que contiene el valor de la variable,
 * o NULL si no se encuentra
 */
char *get_environment_variable(char **env_copy, const char *var)
{
	size_t var_len = strlen(var);
	size_t i;

	for (i = 0; env_copy[i] != NULL; i++)
	{
		if (strncmp(env_copy[i], var, var_len) == 0 && env_copy[i][var_len] == '=')
		{
			return (env_copy[i] + var_len + 1);
		}
	}
	return (NULL);
}

/**
 * print_environment - Imprime el entorno actual
 *
 * Esta función imprime todas las variables de entorno del arreglo de cadenas
 * proporcionado, que representa el entorno actual.
 */
void print_environment(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}
