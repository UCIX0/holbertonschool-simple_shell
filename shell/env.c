#include "main.h"

/**
 * get_environment_copy - Obtiene una copia del entorno actual del programa
 *
 * Esta función utiliza la variable global 'environ' en C, que es un puntero a
 * un arreglo de cadenas que representa el entorno actual del programa, y crea
 * una copia de ese entorno.
 *
 * Return: Un puntero a un arreglo de cadenas que contiene la copia del entorno
 */
char **get_environment_copy()
{
	size_t env_size;
	char **env_copy;

	env_size = get_environment_size();
	env_copy = copy_environment(environ, env_size);
	return (env_copy);
}

/**
 * get_environment_size - Determina el tamaño del entorno
 *
 * Esta función itera sobre el arreglo de cadenas 'environ'
 * y cuenta el número
 * de elementos (variables de entorno) hasta encontrar un puntero nulo, que
 * indica el final del arreglo.
 *
 * Return: El tamaño del entorno, como un valor de tipo size_t
 */
size_t get_environment_size(void)
{
	size_t env_size = 0;

	while (environ[env_size] != NULL)
	{
		env_size++;
	}
	return (env_size);
}


/**
 * copy_environment - Crea una copia del entorno
 * @env: puntero al arreglo de cadenas que representa el entorno a copiar
 * @env_size: tamaño del entorno a copiar
 *
 * Esta función reserva memoria para un nuevo arreglo de cadenas del mismo
 * tamaño que el entorno actual más un elemento adicional
 * para el puntero nulo.
 * Luego copia las variables de entorno al nuevo arreglo.
 *
 * Return: Un puntero a un arreglo de cadenas que contiene la copia del entorno
 */
char **copy_environment(char **env, size_t env_size)
{
	char **env_copy = (char **)malloc((env_size + 1) * sizeof(char *));
	size_t i;

	if (!env_copy)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < env_size; i++)
	{
		env_copy[i] = strdup(env[i]);
		if (!env_copy[i])
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}
	}
	env_copy[env_size] = NULL;
	return (env_copy);
}
