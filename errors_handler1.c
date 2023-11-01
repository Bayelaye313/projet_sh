#include "shell.h"
/**
 * print_command_not_found - Print error message for command not found
 *
 * @info: Pointer to the shell's state_t structure
 * @command: The command that was not found
 */
void print_command_not_found(state_t *info, const char *command)
{
	my_fputs(info->prog, STDERR_FILENO);
	my_fputs(": ", STDERR_FILENO);
	my_fprintf(stderr, "%d", info->linum);
	my_fputs(": ", STDERR_FILENO);
	my_fputs(command, STDERR_FILENO);
	my_fputs(": not found\n", STDERR_FILENO);
	info->errno_val = EKEYEXPIRED;
}
/**
 * print_syntax_error - Print error message for syntax error
 *
 * @info: Pointer to the shell's state_t structure
 * @op: The unexpected operator (1 for '&&', 0 for '||')
 */
void print_syntax_error(state_t *info, int op)
{
	my_fputs(info->prog, STDERR_FILENO);
	my_fputs(": ", STDERR_FILENO);
	my_fprintf(stderr, "%d", info->linum);
	my_fputs(": Syntax error: \"", STDERR_FILENO);
	my_fputs(op == 1 ? "&&" : "||", STDERR_FILENO);
	my_fputs("\" unexpected\n", STDERR_FILENO);
}
/**
 * print_cant_open - Print error message for inability to open file
 *
 * @info: Pointer to the shell's state_t structure
 * @path: The path to the file that couldn't be opened
 */
void print_cant_open(state_t *info, const char *path)
{
	my_fputs(info->prog, STDERR_FILENO);
	my_fputs(": 0: Can't open ", STDERR_FILENO);
	my_fputs(path, STDERR_FILENO);
	_putc('\n', STDERR_FILENO);
}
/**
 * print_errno - Print error message with errno
 *
 * @info: Pointer to the shell's state_t structure
 * @arg: The argument causing the error
 * @err: The errno value
 */
void print_errno(state_t *info, const char *arg, int err)
{
	my_fputs(info->prog, STDERR_FILENO);
	my_fputs(": ", STDERR_FILENO);
	my_fprintf(stderr, "%d", info->linum);
	my_fputs(": ", STDERR_FILENO);
	my_fputs(arg, STDERR_FILENO);
	my_fputs(": ", STDERR_FILENO);
	my_fputs(strerror(err), STDERR_FILENO);
	_putc('\n', STDERR_FILENO);
}
