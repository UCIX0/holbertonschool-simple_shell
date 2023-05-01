#include "main.h"

char **tokenizemin(char *str) {
    int size;
    char *token;
    char **tokens = malloc(sizeof(char *));
    if (!tokens) {
        return NULL;
    }

    size = 1;
    token = strtok(str, " \t\n");
    while (token) {
        tokens = realloc(tokens, sizeof(char *) * (size + 1));
        if (!tokens) {
            return NULL;
        }

        tokens[size - 1] = strdup(token);
        if (!tokens[size - 1]) {
            return NULL;
        }
        tokens[size] = NULL;

        size++;
        token = strtok(NULL, " \t\n");
    }

    return tokens;
}
