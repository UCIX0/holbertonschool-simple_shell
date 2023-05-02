#include "main.h"
/**
 * trim - Elimina los espacios en blanco al inicio y final de una cadena
 * @str: puntero a la cadena de caracteres a recortar
 *
 * La función avanza el puntero al primer carácter que no sea un espacio en
 * blanco y luego, desde el final de la cadena, busca el último carácter que
 * no sea un espacio en blanco. Coloca un carácter nulo después de dicho
 * carácter para terminar la cadena recortada.
 *
 * Return: puntero a la cadena recortada
 */
char *trim(char *str)
{
	char *end;

	while (isspace((unsigned char)*str))
	{
		str++;
	}

	if (*str == '\0')
	{
		return (str);
	}

	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
	{
		end--;
	}

	end[1] = '\0';
	return (str);
}
