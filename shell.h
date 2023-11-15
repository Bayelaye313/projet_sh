#ifndef SHELL_H
#define SHELL_H
#define FRCHAR(n) (n * sizeof(char))
extern char **environ;

/* ---------------- Inclusion des Bibliothèques --------------------- */
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

/* ---------------- Le prompteur ------------------- */
void prompt(void);
char *_getline(int fd);
char *getlines(int fd);

/* --------- Memory Gestion ---------- */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void _memset(char *str, int fill, int n);

/* ---------------- Execute Program ------------------- */
/* ******* Process ********/
void runcommand(state_t *info, char **command);
int exec_line(state_t *info, char *line);
int execute(const char *argv, char *args[], char *env[]);

/* ****** Run Command ****/
bool exec_builtin(state_t *info, char **arguments);
int run_exec(state_t *info, char **arguments);

/* ***** Process Function ****/
char *process_string(state_t *info, char *str);
void process_tokens(state_t *info, char **tokens);
int is_logical(char **tokens, int index, int *next);

/* --------------- Get Absolute Path ---------------- */
bool is_arg(const char *s);
char *get_absolute_path(const char *command, const char *PATH);

/* Shell Handler Functions */
void free_list(node *head);
state_t *init_sh(char *prog, char **env);
void destroy_sh(state_t *info);
void free_inf(state_t *info);

/* -------------- Errors Handler 1 ------------------ */
void print_command_not_found(state_t *info, const char *command);
void print_syntax_error(state_t *info, int op);
void print_cant_open(state_t *info, const char *path);
void print_errno(state_t *info, const char *arg, int err);

/* -------------- Errors Handler 2 ------------------ */
void print_exit_error(state_t *info, const char *arg);
void print_unsetenv_error(const char *target_var);
void print_cd_illegal_option(state_t *info, char option);
void print_cd_cant_change(state_t *info, const char *path);
void print_permission_denied(state_t *info, char **arguments);

/* --------- My Printers 1 Functions ---------------- */
void process_format(FILE *file, const char *format, va_list args);
void my_fprintf(FILE *file, const char *format, ...);
int myprintf(const char *str, ...);
void print_error(const char *message);
void fprinterr(char *message);

/* --------- My Printers 2 Functions ---------------- */
void my_fputs(const char *str, int fd);
void _putc(char c, int fd);
int _putchar(char c);
void my_fputc(char c, FILE *file);

/* ---------- Strings Functions ------------------ */
char *_strtok(char *string, const char *cutter);
char *_strchr(char *s, char c);
int _strlen(const char *s);
char *_strdup(const char *str);
int _strcmp(const char *s1, const char *s2);
int _atoi(char *s);
bool join_char(char **string, size_t *size, char chr, int index);

/* -------------- Useful Functions -------------- */
void handle_hashtag(char *line);
char *rm_quotes(char *str);
int findquote(char *str, char quote);
int join_int(char **string, size_t *size, int num, int index);

/* Formatage */
char *make_format(const char *fm, ...);
void process_integer(FILE *file, int num);

/* -------------- Tokenization ------------------ */
char **split_line(char *string, char *delimiter, unsigned int max);

#endif
