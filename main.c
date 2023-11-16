#include "shell.h"

/**
 * sigint_handler - Handles the SIGINT signal (Ctrl+C).
 * @signum: The signal number (unused).
 *
 * This function is called when the user presses Ctrl+C.
 * prints a newline and then prompts for input,handling the interrupt signal.
 */
void sigint_handler(int signum)
{
	(void)signum;
	myprintf("\n");
	prompt();
}

/**
 * open_file - Opens a file and sets the file descriptor in the shell's state.
 *
 * @info: Pointer to the shell's state_t structure.
 * @path: The path of the file to open.
 *
 * Return: The open file descriptor.
 */
int open_file(state_t *info, char *path)
{
	int fd = open(path, O_RDONLY);

	if (fd == -1)
	{
		print_cant_open(info->prog, 0, path);
		destroy_sh(info);
		exit(127);
	}

	info->fd = fd;
	return (fd);
}

/**
 * run_shell - Runs the shell in either interactive or non-interactive mode.
 *
 * @info: Pointer to the shell's state_t structure.
 * @fd: File descriptor to read input from.
 * @interactive_mode: Flag indicating whether the shell is in interactive mode.
 */
void run_shell(state_t *info, int fd, int interactive_mode)
{
	char *input, **lines, **toks;
	int l, i;

	input = _getline(fd);
	if (!input)
		return;

	info->input = input;
	lines = split_line(input, (interactive_mode ? "\n" : ";"), 0);
	if (!lines)
		return;

	info->lines = lines;
	for (l = 0; lines[l]; l++)
	{
		info->linum = l + 1;
		comment(lines[l]);
		toks = split_line(lines[l], ";", 0);
		if (!toks)
			continue;

		info->toks = toks;
		for (i = 0; toks[i]; i++)
			exec_line(info, toks[i]);

		free(toks);
		info->toks = NULL;
	}

	free_inf(info);
}

/**
 * main - Entry point of the shell program.
 *
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 * @env: Array of environment variable strings.
 *
 * Return: The exit status of the shell program.
 */
int main(int argc, char **argv, char **env)
{
	int status;
	state_t *info;
	int fd = STDIN_FILENO;

	(void)argc;
	signal(SIGINT, sigint_handler);
	info = init_sh(argv[0], env);

	if (argv[1])
		fd = open_file(info, argv[1]);

	run_shell(info, fd, isatty(fd));

	status = info->errno_val;
	destroy_sh(info);
	return (status);
}
