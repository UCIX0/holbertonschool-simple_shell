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
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUFFER_SIZE 1024

extern char **environ;

/**
 * struct TokenizedInputPIPE - estructura para almacenar comandos
 *  y delimitadores (&& ; ||)
 * @commands: arreglo de cadenas de caracteres con los comandos
 * @delimiters: arreglo de cadenas de caracteres con los delimitadores(&& ; ||)
 * @num_commands: número de comandos en el arreglo 'commands'
 * @num_delimiters: número de delimitadores en el arreglo 'delimitadores'
 * La estructura TokenizedInputPIPE almacena los comandos y delimitadores
 * de una entrada, junto con la cantidad de comandos y delimitadores
 * almacenados.
 */
typedef struct TokenizedInputPIPE
{
	char **commands;
	char **delimiters;
	int num_commands;
	int num_delimiters;
} TokenizedInputPIPE;

int main_interactive(void);
int main_non_interactive(char *arg0);

void print_prompt(void);
char *read_input();
void handle_sigint(int sig);
void handle_sigterm(int sig);
void setup_signal_handlers(void);
void remove_comments(char *input);

int check_arguments_and_terminal(void);

int count_elements(char **ptr);

char **get_environment_copy(void);
size_t get_environment_size(void);
char **copy_environment(char **env, size_t env_size);

int my_setenv(char ***env, const char *var, const char *value);
int my_unsetenv(char ***env, const char *var);
void print_environment(void);


char *get_path_variable(char **env_copy);

char **tokenize_path(const char *path_value);
size_t count_paths(const char *path_value);
void copy_paths(char **paths, const char *path_value);

char *get_environment_variable(char **env_copy, const char *var);

char **tokenize_string(const char *input);

TokenizedInputPIPE tokenize_inputpipe(char *input);
int find_delimiter(const char *comst, const char **delm, int numdelm);
void add_command(TokenizedInputPIPE *rs, const char *comst, const char *dlpst);
void add_delimiter(TokenizedInputPIPE *result, const char *delimiter);

char *find_executable(const char *cmd, char **path_dirs, int mode, char *arg0);

int execute(char *commandu, char **paths, int mode, char *arg0);
int execve_without_arg(const char *program);
int execute_with_args(const char *path, char **args, int count);

void free_tokenized_input_pipe(TokenizedInputPIPE *input);
void free_double_pointer(char **ptr, int count);

int execve_builtin(char **cmmdunittokens);
int my_cd(const char *path);
#endif
