#include "shell.h"
/**
 * sigint_handler - Handles the SIGINT signal (Ctrl+C).
 * @signum: The signal number (unused).
 *
 * This function is called when the user presses Ctrl+C. It prints a newline
 * and then prompts for input, effectively handling the interrupt signal.
 */
void sigint_handler(int signum)
{
	(void)signum;
	myprintf("\n"); /* Print a newline after Ctrl+C */
	prompt();       /* Display the prompt after Ctrl+C */
}

/**
 * open_file - used by the main function to open a file
 *
 * @info: the shell's state
 * @path: the path of the file
 *
 * Return: the open file descriptor
 */
int open_file(state_t *info, char *path)
{
	int fd;

	fd = open(path, O_RDONLY);

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
 * interargctive - runs the shell in interargctive mode
 *
 * @info: the shell's state_t
 *
 * Return: always 0
 */
int interargctive(state_t *info)
{
	int l;
	char *input;
	char **toks;

	for (; true; info->linum++)
	{
		prompt();
		input = _getline(STDIN_FILENO);
		if (!input)
		{
			myprintf("\n");
			break;
		}
		info->input = input;
		comment(input);
		toks = split_line(input, ";", 0);
		if (!toks)
		{
			free_inf(info);
			continue;
		}
		info->toks = toks;
		for (l = 0; toks[l]; l++)
		{
			exec_line(info, toks[l]);
		}
		free_inf(info);
	}
	return (0);
}

/**
 * non_interargctive - run shell in non-interargctive mode
 * all commands would be read from a file.
 *
 * @info: shell's state_t
 * @fd: descriptor of file to read from
 *
 * Return: always 0
 */
int non_interargctive(state_t *info, int fd)
{
	int l, i;
	char *input, **lines, **toks;

	input = _getline(fd);
	if (!input)
		return (0);
	info->input = input;
	lines = split_line(input, "\n", 0);
	if (!lines)
		return (0);
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
		{
			exec_line(info, toks[i]);
		}
		free(toks);
		info->toks = NULL;
	}
	free_inf(info);
	return (0);
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
	int fd;

	(void)argc;
	fd = STDIN_FILENO;
	signal(SIGINT, sigint_handler);
	info = init_sh(argv[0], env);

	if (argv[1])
		fd = open_file(info, argv[1]);
	if (isatty(fd))
		interargctive(info);
	else
		non_interargctive(info, fd);
	status = info->errno_val;
	destroy_sh(info);
	return (status);
}
