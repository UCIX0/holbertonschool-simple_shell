#include "main.h"

/**
 * handle_sigint - Maneja la señal SIGINT (Ctrl+C)
 * @sig: número de la señal recibida (no se utiliza en esta función)
 *
 * Esta función se ejecuta cuando se recibe la señal SIGINT. Imprime
 * una nueva línea y muestra nuevamente el símbolo del sistema.
 */
void handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	print_prompt();
}


/**
 * handle_sigterm - Maneja la señal SIGTERM (solicitud de terminación)
 * @sig: número de la señal recibida (no se utiliza en esta función)
 *
 * Esta función se ejecuta cuando se recibe la señal SIGTERM. Termina
 * el proceso con éxito.
 */
void handle_sigterm(int sig)
{
	(void)sig;
	exit(EXIT_SUCCESS);
}

/**
 * setup_signal_handlers - Configura los manejadores de señales
 *
 * Esta función establece los manejadores de señales para SIGINT y
 * SIGTERM, utilizando las funciones handle_sigint y handle_sigterm,
 * respectivamente.
 */
void setup_signal_handlers(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGTERM, handle_sigterm);
}
