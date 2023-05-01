#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <limits.h>

#define BUFFER_SIZE 1024
extern char **environ;

/*Estrucutra de datos de toke.c donde se va alacenar los comandos y los delimitadores
*/
typedef struct {
    char **commands;
    char **delimiters;
    int num_commands;
    int num_delimiters;
} TokenizedInputPIPE;

void print_prompt(void);
char *read_input();
void handle_sigint(int sig);
void handle_sigterm(int sig);
void setup_signal_handlers(void);
void remove_comments(char *input);

int check_arguments_and_terminal(int argc, char **argv);

char **get_environment_copy();
size_t get_environment_size();
char **copy_environment(char **env, size_t env_size);

int my_setenv(char ***env, const char *var, const char *value);
int my_unsetenv(char ***env, const char *var);
void print_environment(char **env);


char *get_path_variable(char **env_copy);
char **tokenize_path(const char *path_value);
char *get_environment_variable(char **env_copy, const char *var);
char *trim(char *str);

TokenizedInputPIPE tokenize_inputpipe(char *input);
int find_delimiter(const char *comst, const char **delm, int numdelm);
void add_command(TokenizedInputPIPE *rs, const char *comst, const char *dlpst);
void add_delimiter(TokenizedInputPIPE *result, const char *delimiter);

int find_executable(const char *cmd, char **path_dirs);
#endif