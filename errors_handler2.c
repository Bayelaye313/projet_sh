#include "shell.h"
/**
 * print_exit_error - Print error message for illegal exit number
 *
 * @info: Pointer to the shell's state_t structure
 * @arg: Argument that caused the error
 */
void print_exit_error(state_t *info, const char *arg)
{
	my_fputs(info->prog, STDERR_FILENO);
	my_fputs(": ", STDERR_FILENO);
	my_fprintf(stderr, "%d", info->linum);
	my_fputs(": exit: Illegal number: ", STDERR_FILENO);
	my_fputs(arg, STDERR_FILENO);
	_putc('\n', STDERR_FILENO);
}
/**
 * print_unsetenv_error - Print error message for unset environment variable
 *
 * @target_var: The variable that does not exist
 */
void print_unsetenv_error(const char *target_var)
{
	my_fputs("unsetenv: ", STDERR_FILENO);
	my_fputs(target_var, STDERR_FILENO);
	my_fputs(" does not exist\n", STDERR_FILENO);
}
/**
 * print_cd_illegal_option - Print error message for illegal 'cd' option
 *
 * @info: Pointer to the shell's state_t structure
 * @option: The illegal option
 */
void print_cd_illegal_option(state_t *info, char option)
{
	my_fprintf(stderr, "%s: %d: cd: Illegal option -%c\n",
			info->prog, info->linum, option);
}
/**
 * print_cd_cant_change - Print error message for failed directory change
 *
 * @info: Pointer to the shell's state_t structure
 * @path: The path that couldn't be accessed
 */
void print_cd_cant_change(state_t *info, const char *path)
{
	my_fprintf(stderr, "%s: %d: cd: can't cd to %s\n",
			info->prog, info->linum, path);
}
/**
 * print_permission_denied - Print a "Permission denied" mesge to stderr.
 * @info: Pointer to a structure containing program information.
 * @arguments: Array of strings containing command arguments.
 *
 * This function prints an error message indicating that perm is denied.
 * It includes the program name, line number, and the first arg in the message.
 */
void print_permission_denied(state_t *info, char **arguments)
{
	FILE *stream = stderr;

	fprintf(stream, "%s: %d: %s: Permission denied\n",
			info->prog, info->linum, arguments[0]);
}
