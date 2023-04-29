#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

char **get_environment_copy();
size_t get_environment_size();
char **copy_environment(char **env, size_t env_size);

/* Obtener el entorno actual del programa
Utiliza la variable global 'environ' en C, que es un puntero a un arreglo de cadenas que representa el entorno actual del programa.*/
char **get_environment_copy() {
    size_t env_size = get_environment_size();
    char **env_copy = copy_environment(environ, env_size);
    return env_copy;
}

/* Determinar el tamaño del entorno
Iterar sobre el arreglo de cadenas 'environ' y contar el número de elementos (variables de entorno) hasta encontrar un puntero nulo, que indica el final del arreglo. */
size_t get_environment_size() {
    size_t env_size = 0;
    while (environ[env_size] != NULL) {
        env_size++;
    }
    return env_size;
}



/*
Crear una copia del entorno
	- Reservar memoria para un nuevo arreglo de cadenas del mismo tamaño que el entorno actual más un elemento adicional para el puntero nulo.
	- Utilizar una función 'malloc' para asignar la memoria necesaria.

Copiar las variables de entorno al nuevo arreglo
	- Iterar sobre el arreglo de cadenas 'environ' y, para cada elemento, reservar memoria para una nueva cadena del mismo tamaño que la cadena original 'malloc'.
	- Utilizar una función como 'strcpy' en C para copiar el contenido de cada cadena del entorno original al nuevo arreglo.
	- Establecer el último elemento del nuevo arreglo como un puntero nulo.
*/
char **copy_environment(char **env, size_t env_size) {
    char **env_copy = (char **)malloc((env_size + 1) * sizeof(char *));
    if (!env_copy) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < env_size; i++) {
        env_copy[i] = strdup(env[i]);
        if (!env_copy[i]) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
    }
    env_copy[env_size] = NULL;
    return env_copy;
}



/*
inicia una nueva variable de entorno o modifique una existente
Sintaxis del comando: setenv VARIABLE VALUE
*/
int my_setenv(char ***env, const char *var, const char *value) {
    size_t env_size = get_environment_size();
    char *new_var = malloc(strlen(var) + strlen(value) + 2);
    if (!new_var) {
        fprintf(stderr, "Error al asignar memoria para la nueva variable.\n");
        return -1;
    }
    sprintf(new_var, "%s=%s", var, value);
    *env = realloc(*env, (env_size + 2) * sizeof(char *));
    if (!*env) {
        fprintf(stderr, "Error al reasignar memoria para el entorno.\n");
        free(new_var);
        return -1;
    }
    (*env)[env_size] = new_var;
    (*env)[env_size + 1] = NULL;
    return 0;
}


/*elimina una variable de entorno
Sintaxis del comando: unsetenv VARIABLE*/
int my_unsetenv(char ***env, const char *var) {
    size_t i = 0, var_len = strlen(var);
    while ((*env)[i] != NULL) {
        if (strncmp((*env)[i], var, var_len) == 0 && (*env)[i][var_len] == '=') {
            free((*env)[i]);
            while ((*env)[i + 1] != NULL) {
                (*env)[i] = (*env)[i + 1];
                i++;
            }
            (*env)[i] = NULL;
            return 0;
        }
        i++;
    }
    fprintf(stderr, "Variable \"%s\" no encontrada.\n", var);
    return -1;
}
/*imprime el entorno actual*/
void print_environment(char **env) {
    for (size_t i = 0; env[i] != NULL; i++) {
        printf("%s\n", env[i]);
    }
}


int shell_start() {
    char **env_copy = get_environment_copy();
    // El resto de tu código shell aquí

    print_environment(env_copy); // Ejemplo de uso de print_environment
    my_setenv(&env_copy, "MY_VARIABLE", "my_value"); // Ejemplo de uso de my_setenv
    print_environment(env_copy); // Ejemplo de uso de print_environment
    my_unsetenv(&env_copy, "MY_VARIABLE"); // Ejemplo de uso de my_unsetenv

    print_environment(env_copy); // Ejemplo de uso de print_environment

    // No olvides liberar la memoria de env_copy antes de salir
    // Liberar memoria
    for (size_t i = 0; env_copy[i] != NULL; i++) {
        free(env_copy[i]);
    }
    free(env_copy);
    return 0;
}
