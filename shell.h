#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct list_node - singly linked list
 * @index: the number field
 * @data: a string
 * @next: points to the next node
 */
typedef struct list_node
{
	int index;
	char *data;
	struct list_node  *next;
} list_node;

/**
 * struct shell_info - contains pseudo-arguments to pass into a function,
 *                     allowing uniform prototype for function pointer struct
 * @input_line: raw input string generated from getline, containing arguments
 * @argv: an array of tokenized strings generated from input_line (argv)
 * @argc: the number of arguments in 'argv'
 * @path: the string path for the current command to be executed
 * @input_line_count: the total count of input lines processed by the shell
 * @count_current_line: indicate if the current input line should be counted
 * @program_name: the name of the shell program (filename)
 * @env: a linked list storing a local copy of environment variables
 * @custom_environ: an array of environment variables derived from 'env'
 * @env_modified: indicating whether the environment variables have changed
 * @history: a linked list storing the command history
 * @history_count: the count of commands stored in the history list
 * @alias: a linked list storing aliases for commands
 * @last_status: the return status of the last executed command
 * @error_code: the error code used for exit statuses
 * @cmd_chain_buf: address of pointer to cmd buffer, used for chaining commands
 * @cmd_chain_type: type of command chaining (CMD_type: ||, &&, ;)
 * @input_fd: file descriptor to read input from (default is stdin)
 */
typedef struct shell_info
{
	/* User input and arguments */
	char *input_line;
	char **argv;
	int argc;
	char *path;

	/* Line and program details */
	unsigned int input_line_count;
	int count_current_line;
	char *program_name;

	/* Environment management */
	list_node *env;
	char **custom_environ;
	int env_modified;

	/* Command history and alias */
	list_node *history;
	int history_count;
	list_node *alias;

	/* Status and command control */
	int last_status;
	int error_code;
	char **cmd_chain_buf; /* pointer to cmd ;chain buffer for memory management */
	int cmd_chain_type;    /* CMD_type ||, &&, ; */

	/* File descriptor and other control variables */
	int input_fd;
} shell_info;

#define SHELL_INFO_INIT \
{   NULL,   /* input_line */ \
	NULL,   /* argv */ \
	0,      /* argc */ \
	NULL,   /* path */ \
	0,      /* input_line_count */ \
	0,      /* count_current_line */ \
	NULL,   /* program_name */ \
	NULL,   /* env */ \
	NULL,   /* custom_environ */ \
	0,      /* env_modified */ \
	NULL,   /* history */ \
	0,      /* history_count */ \
	NULL,   /* alias */ \
	0,      /* last_status */ \
	0,      /* error_code */ \
	NULL,   /* cmd_chain_buf */ \
	0,      /* cmd_chain_type */ \
	0       /* input_fd */ \
}


/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(shell_info *);
} builtin_table;


/* toem_shloop.c */
int hsh(shell_info *, char **);
int find_builtin(shell_info *);
void find_cmd(shell_info *);
void fork_cmd(shell_info *);

/* toem_parser.c */
int is_cmd(shell_info *, char *);
char *dup_chars(char *, int, int);
char *find_path(shell_info *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *find_substring(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(shell_info *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(shell_info *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(shell_info *);
int _mycd(shell_info *);
int _myhelp(shell_info *);

/* toem_builtin1.c */
int _myhistory(shell_info *);
int _myalias(shell_info *);

/*toem_getline.c */
ssize_t get_input(shell_info *);
int _getline(shell_info *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(shell_info *);
void set_info(shell_info *, char **);
void free_info(shell_info *, int);

/* toem_environ.c */
char *get_env_value(shell_info *, const char *);
int _myenv(shell_info *);
int _mysetenv(shell_info *);
int _myunsetenv(shell_info *);
int populate_env_list(shell_info *);

/* toem_getenv.c */
char **get_environ(shell_info *);
int _unsetenv(shell_info *, char *);
int _setenv(shell_info *, char *, char *);

/* toem_history.c */
char *get_history_file(shell_info *info);
int write_history(shell_info *info);
int read_history(shell_info *info);
int build_history_list(shell_info *info, char *buf, int linecount);
int renumber_history(shell_info *info);

/* toem_lists.c */
list_node *add_node(list_node **, const char *, int);
list_node *add_node_end(list_node **, const char *, int);
size_t print_list_str(const list_node *);
int delete_node_at_index(list_node **, unsigned int);
void free_list(list_node **);

/* toem_lists1.c */
size_t list_len(const list_node *);
char **list_to_strings(list_node *);
size_t print_list(const list_node *);
list_node *node_starts_with(list_node *, char *, char);
ssize_t get_node_index(list_node *, list_node *);

/* toem_vars.c */
int is_chain(shell_info *, char *, size_t *);
void check_chain(shell_info *, char *, size_t *, size_t, size_t);
int replace_alias(shell_info *);
int replace_vars(shell_info *);
int replace_string(char **, char *);

#endif
