#ifndef SHELL_H
#define SHELL_H

#define FRPTR(n) (n * sizeof(void *))
#define FRCHAR(n) (n * sizeof(char))
extern char **environ;
#define SIZE_MAX ((size_t)-1)

/*-----------------Inclusion des Bibliothèques------------------------*/
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include "stdbool.h"
#include <signal.h>
#include <string.h>
#include <stdarg.h>
#include "entetes/nodes.h"
#include "entetes/built.h"

/*----------------le prompteur-------------------*/
void prompt(void);
char *_getline(int fd);
int findquote(char *str, char quote);
/*---------memory gestion----------*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void _memset(char *str, int fill, int n);
void _memcpy(char *dest, char *src, unsigned int bytes);

/*----------------execute_prog-------------------*/
/*******process********/
void runcommand(state_t *info, char **command);
int exec_line(state_t *info, char *line);
int execute(const char *argv, char *args[], char *env[]);
/******run_command****/
bool exec_builtin(state_t *info, char **arguments);
int run_exec(state_t *info, char **arguments);
/*****process_func***/
char *process_string(state_t *info, char *str);
void process_tokens(state_t *info, char **tokens);
int is_logical(char **tokens, int index, int *next);

/*---------------get_absolute_path----------------*/
bool is_arg(const char *s);
char *get_absolute_path(const char *command, const char *PATH);
/*shell_handler functions*/
void free_list(node *head);
state_t *init_sh(char *prog, char **env);
void destroy_sh(state_t *info);
void free_inf(state_t *info);

/*--------------errors_handler1------------------*/
void print_command_not_found(state_t *info, const char *command);
void print_syntax_error(state_t *info, int op);
void print_cant_open(state_t *info, const char *path);
void print_errno(state_t *info, const char *arg, int err);

/*--------------errors_handler2------------------*/
void print_exit_error(state_t *info, const char *arg);
void print_unsetenv_error(const char *target_var);
void print_cd_illegal_option(state_t *info, char option);
void print_cd_cant_change(state_t *info, const char *path);
void print_permission_denied(state_t *info, char **arguments);

/*---------Myprinters1 functions----------------*/
void process_format(FILE *file, const char *format, va_list args);
void my_fprintf(FILE *file, const char *format, ...);
int myprintf(const char *str, ...);
void print_error(const char *message);
void fprinterr(char *message);

/*---------Myprinters2 functions----------------*/
void my_fputs(const char *str, int fd);
void _putc(char c, int fd);
int _putchar(char c);
void my_fputc(char c, FILE *file);

/*----------strings functions------------------*/
char *_strtok(char *string, const char *cutter);
char *_strchr(char *s, char c);
char *_strcpy(char *dest, char *src);
int _strlen(const char *s);
char *_strdup(const char *str);
int _strcmp(const char *s1, const char *s2);
char *_strcat(char *dest, const char *src);
int _atoi(char *s);

/*--------------useful_functions--------------*/
void handle_hashtag(char *line);
char *rm_quotes(char *str);
int join_int(char **string, size_t *size, int num, int index);

/*handle format*/
bool join_char(char **string, size_t *size, char chr, int index);
char *make_format(const char *fm, ...);
void process_integer(FILE *file, int num);
/*--------------tokenization------------------*/
char **split_line(char *input, char *delimiter, unsigned int max);



#endif
