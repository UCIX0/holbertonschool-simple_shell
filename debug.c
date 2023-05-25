#include "main.h"
char* concatenarStrings(char** doblePuntero) {
    // Obtener la cantidad total de caracteres necesarios
    int totalCaracteres = 0;
    int numStrings = 0;
    for (int i = 0; doblePuntero[i] != NULL; i++) {
        totalCaracteres += strlen(doblePuntero[i]);
        numStrings++;
    }
    // Cantidad de caracteres para los separadores "---"
    totalCaracteres += (numStrings - 1) * 3;
    
    // Crear un nuevo string para almacenar el resultado
    char* resultado = (char*)malloc((totalCaracteres + 1) * sizeof(char));
    resultado[0] = '\0'; // Inicializar el string vacío
    
    // Concatenar los strings con los separadores
    for (int i = 0; doblePuntero[i] != NULL; i++) {
        strcat(resultado, doblePuntero[i]);
        if (doblePuntero[i + 1] != NULL) {
            strcat(resultado, "---");
        }
    }
    
    return resultado;
}