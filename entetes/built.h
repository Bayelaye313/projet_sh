#ifndef BUILTIN_H
#define BUILTIN_H

#include "./nodes.h"

/**
 * struct state - Contains variables for command line interpretation.
 *
 * @linum: Current line number.
 * @errno_val: Number indicating the error of the last command.
 * @fd: Open file descriptor for reading commands.
 * @prog: Program name used to start the shell.
 * @buf: Free buffer available for any function to use.
 * @pid_buf: A buffer that'll be used to hold the program's pid.
 * @errno_buf: A buffer that'll be used to hold the program's errno.
 * @input: Command line inputs.
 * @lines: Array of lines from inputs.
 * @toks: Array of tokens from a line separated by semicolons.
 * @tokens: Array of tokens found in a line/part.
 * @command: Array of tokens gotten from parsing alias.
 * @env: Shell environment variables.
 */
typedef struct state {
    int linum;
    int errno_val;
    int fd;
    char *prog;
    char *buf;
    char *pid_buf;
    char *errno_buf;
    char *input;
    char **lines;
    char **toks;
    char **command;
    char **tokens;
    node *env;
    node *aliase
} state_t;

/**
 * builtincmd - Typedef for a built-in command function pointer.
 *
 * @info: Pointer to state_t structure.
 * @arguments: Array of command arguments.
 *
 * Return: Integer indicating command status.
 */
typedef int (*builtincmd)(state_t *, char **);

/**
 * struct builtin - Represents a shell builtin command.
 *
 * @name: The name of the builtin.
 * @handler: The function that handles the builtin command.
 */
typedef struct builtin
{
    char *name;
    builtincmd handler;
} builtin_t;


/*builtins functions*/
int my_exit(state_t *info, char **args);
int my_cd(state_t *info, char **args);


/*cd functions*/
int cd_to_home(state_t *info __attribute__((unused)));
int cd_to_previous(state_t *info __attribute__((unused)));
int cd_illegal_option(state_t *info, char option);

/*environs*/
int my_env(state_t *info, char **args);
int _setenv(state_t *info, char **args);
int _unsetenv(state_t *info, char **args);
/*alias*/
int set_alias(state_t *info, char *str);
int unset_alias(state_t *info, char *str);
int _alias(state_t *info, char **args);
#endif

