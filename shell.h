#ifndef _MYSHELL_HEADER_
#define _MYSHELL_HEADER_

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
#define BUFFER_R 1024
#define BUFFER_W 1024
#define FLUSH -1

/* for command chaining */
#define COMMAND_OK	0
#define COMMAND_OR		1
#define COMMAND_AND		2
#define COMMAND_CHAINS	3

/* for convert_number() */
#define TO_LOWER	1
#define TO_UNSIGNED	2

/* 1 if using system getline() */
#define GETLINE 0
#define STRTOK 0

#define HISTORY_	".simple_shell_history"
#define LIMIT_TO_HIST	4096

extern char **environ;


/**
 * struct strlist - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct strlist
{
	int num;
	char *str;
	struct strlist *next;
} lists_;

/**
 * struct relayinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_counts: the error count
 * @num_error: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @filename: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @buffer_command: address of pointer to buffer_command, on if chaining
 * @buffer_command_type: CMD_type ||, &&, ;
 * @read_filedescripter: the file_d from which to read line input
 * @histcount: the history line number count
 */
typedef struct relayinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_counts;
	int num_error;
	int linecount_flag;
	char *filename;
	lists_ *env;
	lists_ *history;
	lists_ *alias;
	char **environ;
	int env_changed;
	int status;
	char **buffer_command;/* pointer to cmd; chain buffer, for memory mangement */
	int buffer_command_type; /* CMD_type ||, &&, ; */
	int read_filedescripter;
	int histcount;
} info_t;

#define INITIAL_STATUS \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* _shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* _parser.c */
int is_command(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* hshloop.c */
int hshloop(char **);

/* _errors.c */
void eputs_(char *);
int eputchar_(char);
int putfile_descripter_(char c, int file_d);
int putsfile_descripter_(char *str, int file_d);

/* _string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* _string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* _exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* _tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* _realloc.c */
char *_setmemory(char *, char, unsigned int);
void free_f(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* _memory.c */
int free_buffer(void **);

/* _str_to_int.c */
int interactive(info_t *);
int for_delimiter(char, char *);
int _for_alphabet(int);
int _str_to_int(char *);

/* _errors1.c */
int _errstr_to_int(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* _builtin.c */
int _to_exit(info_t *);
int _change_directory(info_t *);
int _for_help(info_t *);

/* _builtin1.c */
int __history_(info_t *);
int __alias_(info_t *);

/*_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* _getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* _environ.c */
char *_getenv(info_t *, const char *);
int __env(info_t *);
int __setenv(info_t *);
int __unsetenv(info_t *);
int populate_env_list(info_t *);

/* _getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* _history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int reorder_history(info_t *info);

/* _lists.c */
lists_ *add_node(lists_ **, const char *, int);
lists_ *add_node_end(lists_ **, const char *, int);
size_t print_list_str(const lists_ *);
int delete_node_at_index(lists_ **, unsigned int);
void free_list(lists_ **);

/* _lists1.c */
size_t list_len(const lists_ *);
char **lists_o_strings(lists_ *);
size_t print_list(const lists_ *);
lists_ *node_starts_with(lists_ *, char *, char);
ssize_t get_node_index(lists_ *, lists_ *);

/* _vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
