#include "main.h"
/**
 * execute - Ejecuta un comando con argumentos dados y busca el ejecutable
 * @commandu: cadena de caracteres que contiene el comando y sus argumentos
 * @paths: arreglo de directorios de PATH en los que buscar el ejecutable
 * @mode: parametro que se le pasa a find_executable elegir
 * para elejir el modo de imprimir el error
 * @arg0: nombre de la shell para imprimir en el mensaje de error
 *
 * La función recibe un comando y sus argumentos, busca el ejecutable en los
 * directorios especificados y lo ejecuta. Si el comando
 * no necesita argumentos, se llama a la función 'execve_without_arg'.
 * Si necesita argumentos, se llama a la función 'execute_with_args'.
 *
 * Return: código de salida del comando ejecutado, -1 en caso de error
 */
int execute(char *commandu, char **paths, int mode, char *arg0)
{
	char **cmmdunittokens;
	int status;
	char *command_path = NULL;
	int countelements;
	int statusb = 0;

	cmmdunittokens = tokenize_string(commandu);
	if (cmmdunittokens[0] == NULL)
	{
		free_double_pointer(cmmdunittokens, count_elements(cmmdunittokens));
		return (-1);
	}
	statusb = execve_builtin(cmmdunittokens);
	if (statusb == -1)
	{
		command_path = find_executable(cmmdunittokens[0], paths, mode, arg0);
	}
	countelements = count_elements(cmmdunittokens);
	if (command_path != NULL)
	{
		if (countelements == 1)
		{
			status = execve_without_arg(command_path);
		}
		else
		{
			status = execute_with_args(command_path, cmmdunittokens, countelements);
		}
	}
	free_double_pointer(cmmdunittokens, count_elements(cmmdunittokens));
	free(command_path);
	return (status);
}


/**
 * execve_without_arg - Ejecuta un programa sin argumentos
 * @program: ruta del programa a ejecutar
 *
 * La función crea un proceso hijo y ejecuta el programa especificado sin
 * argumentos en ese proceso.
 *
 * Return: código de salida del programa ejecutado, -1 en caso de error
 */
int execve_without_arg(const char *program)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	} else if (pid == 0)
	{
		char *argv[2];

		argv[0] = (char *) program;
		argv[1] = NULL;

		if (execve(program, argv, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	} else
	{
		if (waitpid(pid, &status, 0) < 0)
		{
			perror("waitpid");
			return (-1);
		}
		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
		}
			fprintf(stderr, "Error: child process terminated abnormally.\n");
			return (-1);
	}
	return (0);
}

/**
 * prepare_exec_args - Prepara el arreglo con ragumentos para 'execve'
 * @path: ruta del programa a ejecutar
 * @tokenz: arreglo de caracteres con los tokens de la línea de comandos
 * @count: número de argumentos en el arreglo
 *
 * La función crea un nuevo arreglo con el nombre del programa
 * como primer elemento y los argumentos en las posiciones
 * siguientes con terminación en NULL.
 * El arreglo se usa como argumento para la función 'execve'.
 *
 * Return: puntero al arreglo de argumentos, NULL en caso de error
 */
char **prepare_exec_args(const char *path, char **tokenz, int count)
{
	int i;
	char **exec_args;

	exec_args = malloc((count + 1) * sizeof(char *));
	if (!exec_args)
	{
		perror("malloc");
		return (NULL);
	}

	exec_args[0] = (char *)path;
	for (i = 1; i < count; i++)
	{
		exec_args[i] = tokenz[i];
	}
	exec_args[count] = NULL;

	return (exec_args);
}


/**
 * execute_child - Ejecuta el programa y los argumentos en un proceso hijo
 * @path: ruta del programa a ejecutar
 * @exec_args: arreglo de caracteres con la ruta y los argumentos,
 * terminado con NUll
 *
 * La función ejecuta el programa y los argumentos en el proceso hijo y
 * libera la memoria asignada a 'exec_args' antes de terminar el proceso.
 *
 * Return: 0 si se ejecuta correctamente, -1 en caso de error
 */
int execute_child(const char *path, char **exec_args)
{
	if (execve(path, exec_args, NULL) < 0)
	{
		perror("execve");
		free(exec_args);
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * execute_with_args - Ejecuta un programa con argumentos
 * @path: ruta del programa a ejecutar
 * @tokens: arreglo de caracteres con los tokens de la línea de comandos
 * @count: número de tokens en el arreglo
 *
 * La función crea un proceso hijo y ejecuta el programa especificado con
 * los argumentos proporcionados en ese proceso.
 *
 * Return: código de salida del programa ejecutado, -1 en caso de error
 */
int execute_with_args(const char *path, char **tokens, int count)
{
	pid_t pid;
	char **exec_args;
	int status;

	exec_args = prepare_exec_args(path, tokens, count);
	if (!exec_args)
	{
		return (-1);
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(exec_args);
		return (-1);
	}
	else if (pid == 0)
	{
		return (execute_child(path, exec_args));
	}
	else
	{
		if (waitpid(pid, &status, 0) < 0)
		{
			perror("waitpid");
			free(exec_args);
			return (-1);
		}
		free(exec_args);
		return ((WIFEXITED(status)
		&& WEXITSTATUS(status) == EXIT_SUCCESS) ? 0 : WEXITSTATUS(status));
	}
}
