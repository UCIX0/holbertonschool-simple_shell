#include "main.h"

/**
 * my_setenv - Inicia una nueva variable de entorno
 * o modifica una existente
 * @env: puntero doble al arreglo de cadenas
 * que representa el entorno
 * @var: puntero a la cadena de caracteres
 * que contiene el nombre de la variable
 * @value: puntero a la cadena de caracteres
 * que contiene el valor de la variable
 *
 * Esta función crea o modifica una variable de entorno con el nombre y valor
 * especificados. Si la variable ya existe, su valor se reemplaza.
 * Sintaxis del comando: setenv VARIABLE VALUE
 *
 * Return: 0 si la operación fue exitosa, -1 si hubo un error
 */
int my_setenv(char ***env, const char *var, const char *value)
{
	size_t env_size = get_environment_size();
	char *new_var = malloc(strlen(var) + strlen(value) + 2);

	if (!new_var)
	{
		fprintf(stderr, "Error al asignar memoria para la nueva variable.\n");
		return (-1);
	}
	sprintf(new_var, "%s=%s", var, value);
	*env = realloc(*env, (env_size + 2) * sizeof(char *));
	if (!*env)
	{
		fprintf(stderr, "Error al reasignar memoria para el entorno.\n");
		free(new_var);
		return (-1);
	}
	(*env)[env_size] = new_var;
	(*env)[env_size + 1] = NULL;
	return (0);
}


/**
 * my_unsetenv - Elimina una variable de entorno
 * @env: puntero doble al arreglo de cadenas
 * que representa el entorno
 * @var: puntero a la cadena de caracteres
 * que contiene el nombre de la variable
 *
 * Esta función elimina una variable de entorno con el nombre especificado.
 * Sintaxis del comando: unsetenv VARIABLE
 *
 * Return: 0 si la operación fue exitosa, -1 si la variable no se encontró
 */
int my_unsetenv(char ***env, const char *var)
{
	size_t i = 0, var_len = strlen(var);

	while ((*env)[i] != NULL)
	{
		if (strncmp((*env)[i], var, var_len) == 0 && (*env)[i][var_len] == '=')
		{
			free((*env)[i]);
			while ((*env)[i + 1] != NULL)
			{
				(*env)[i] = (*env)[i + 1];
				i++;
			}
			(*env)[i] = NULL;
			return (0);
		}
		i++;
	}
	fprintf(stderr, "Variable \"%s\" no encontrada.\n", var);
	return (-1);
}
