#ifndef BUILTIN_H
#define BUILTIN_H

#include "./nodes.h"

/**
 * struct state - Contains variables for command line interpretation.
 *
 * @linum: Current line number.
 * @errno_val: Last command error's number.
 * @fd: Open file descriptor for reading commands.
 * @prog: Name of the program used to start the shell.
 * @buf: Buffer for freeing memory.
 * @pid_buf: Buffer used for handling process IDs.
 * @errno_buf: Buffer used for handling errno.
 * @input: Command line inputs.
 * @lines: Array of lines from inputs.
 * @toks: Array of tokens from a line separated by semicolons.
 * @tokens: Array of tokens found in a line by parsing.
 * @env: Shell environment variables.
 */
typedef struct state
{
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
	char **tokens;
	node *env;
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


/* Builtin Functions */
int my_exit(state_t *info, char **args);
int my_cd(state_t *info, char **args);

/* CD Functions */
int cd_to_home(state_t *info __attribute__((unused)));
int cd_to_previous(state_t *info __attribute__((unused)));
int cd_illegal_option(state_t *info, char option);

/* Environment Functions */
int my_env(state_t *info, char **args);
int _setenv(state_t *info, char **args);
int _unsetenv(state_t *info, char **args);

#endif
