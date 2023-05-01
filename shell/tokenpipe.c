#include "main.h"
/**
 * find_delimiter - Encuentra la posición del primer
 * delimitador en una cadena
 * @comst: puntero a la cadenas en la que se buscará el delimitador
 * @delm: puntero al arreglos de cadenas que contiene
 * los delimitadores posibles
 * @numdelm: cantidad de delimitadores en el arreglo
 * Return: El índice del delimitador encontrado
 * o -1 si no se encuentra ninguno
 */
int find_delimiter(const char *comst, const char **delm, int numdelm)
{
	char *delimiter_pos = NULL;
	int i;
	int delimiter_index = -1;

	for (i = 0; i < numdelm; ++i)
	{
		char *pos = strstr(comst, delm[i]);

		if (pos != NULL && (delimiter_pos == NULL || pos < delimiter_pos))
		{
			delimiter_pos = pos;
			delimiter_index = i;
		}
	}
	return (delimiter_index);
}
/**
 * add_command - Agrega un comando al objeto TokenizedInputPIPE
 * @rs: puntero al objeto TokenizedInputPIPE en el que se agregará el comando
 * @comst: puntero al inicio del comando en la cadena de entrada
 * @dlpst: puntero a la posición del delimitador en la cadena de entrada
 * Esta función agrega un comando al objeto TokenizedInputPIPE, copiando
 * el comando desde la cadena de entrada y ajustando el tamaño del arreglo
 * de comandos en el objeto.
 */
void add_command(TokenizedInputPIPE *rs, const char *comst, const char *dlpst)
{
	TokenizedInputPIPE *result = rs;
	const char *delimiter_pos = dlpst;
	size_t command_len = delimiter_pos - comst;
	char *trimmed_command;
	char *command = (char *)malloc((command_len + 1) * sizeof(char));
	size_t new_size;

	strncpy(command, comst, command_len);
	command[command_len] = '\0';
	trimmed_command = trim(command);
	result->commands[result->num_commands] = strdup(trimmed_command);
	free(command);
	++result->num_commands;
	new_size = (result->num_commands + 1) * sizeof(char *);
	result->commands = (char **)realloc(result->commands, new_size);
}
/**
 * add_delimiter - Agrega un delimitador al objeto TokenizedInputPIPE
 * @result: puntero al objeto TokenizedInputPIPE
 * en el que se agregará el delimitador
 * @delimiter: puntero a la cadena de caracteres que contiene el delimitador
 *
 * Esta función agrega un delimitador al objeto TokenizedInputPIPE y ajusta
 * el tamaño del arreglo de delimitadores en el objeto.
 */
void add_delimiter(TokenizedInputPIPE *result, const char *delimiter)
{
	size_t new_size;

	result->delimiters[result->num_delimiters] = strdup(delimiter);
	++result->num_delimiters;
	new_size = (result->num_delimiters + 1) * sizeof(char *);
	result->delimiters = (char **)realloc(result->delimiters, new_size);
}

/**
 * tokenize_inputpipe - Divide una cadena de entrada
 * en comandos y delimitadores
 * @input: puntero a la cadena de caracteres
 * que contiene la entrada
 *
 * Esta función divide la cadena de entrada en comandos y delimitadores,
 * y guarda los resultados en un objeto TokenizedInputPIPE.
 *
 * Return: Un objeto TokenizedInputPIPE
 * que contiene los comandos y delimitadores
 */
TokenizedInputPIPE tokenize_inputpipe(char *input)
{
	const char *delimiters[] = {";", "&&", "||"};
	int num_delimiters = sizeof(delimiters) / sizeof(delimiters[0]);
	char *comst = input;
	TokenizedInputPIPE result;

	result.commands = (char **)malloc(sizeof(char *));
	result.delimiters = (char **)malloc(sizeof(char *));
	result.num_commands = 0;
	result.num_delimiters = 0;

	while (*comst != '\0')
	{
		int delimiter_index = find_delimiter(comst, delimiters, num_delimiters);
		char *delimiter_pos = NULL;

		if (delimiter_index != -1)
		{
			delimiter_pos = strstr(comst, delimiters[delimiter_index]);
			add_command(&result, comst, delimiter_pos);
			add_delimiter(&result, delimiters[delimiter_index]);
			comst = delimiter_pos + strlen(delimiters[delimiter_index]);
		}
		else
		{
			char *trimmed_command = trim(comst);

			result.commands[result.num_commands] = strdup(trimmed_command);
			++result.num_commands;
			break;
		}
	}

	return (result);
}
