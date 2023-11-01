#include "shell.h"
/**
 * open_file - Attempts to open a file for reading.
 *
 * @info: Pointer to the shell's state_t.
 * @path: Path to the file to be opened.
 *
 * Return: The file descriptor if successful, or -1 on failure.
 * If an error occurs, it may also exit the program with
 * the appropriate error code.
 */
int open_file(state_t *info, char *path)
{
	info->fd = open(path, O_RDONLY);

	if (info->fd == -1)
	{
		if (errno == EACCES)
			exit(126);
		if (errno == ENOENT)
		{
			print_cant_open(info, path);
			destroy_sh(info);
			exit(127);
		}
	}
	return (info->fd);
}
/**
 * process_input - Processes input and executes corresponding commands.
 *
 * @info: Pointer to state_t structure.
 * @input: Input string to process.
 */
void process_input(state_t *info, char *input)
{
	int l;
	char **toks;

	info->input = input;
    handle_hashtag(input);
	toks = split_line(input, ";", 0);
	if (!toks)
	{
		free_inf(info);
		return;
	}
	info->toks = toks;
	for (l = 0; toks[l]; l++)
	{
		exec_line(info, toks[l]);
	}
	free_inf(info);
}
/**
 * process_input_interactive - Handles interactive mode input processing.
 *
 * @info: Pointer to the state structure.
 */
void process_input_interactive(state_t *info)
{
	char *input;

	while (1)
	{
		prompt();
		input = _getlines(STDIN_FILENO);
		if (!input)
		{
			myprintf("\n");
			break;
		}
		process_input(info, input);
	}
}
/**
 * process_input_noninteractive - Processes non-interactive input.
 *
 * @info: Pointer to state_t structure.
 * @fd: File descriptor for input.
 */
void process_input_noninteractive(state_t *info, int fd)
{
	char *input = _getlines(fd);

	if (!input)
	{
		destroy_sh(info);
		return;
	}
	process_input(info, input);
	free(input);
}
/**
 * main - Entry point of the shell program.
 *
 * @ac: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 * @env: Array of environment variable strings.
 *
 * Return: The exit status of the shell program.
 */
int main(int ac, char **argv, char **env)
{
	int status, fd;
	state_t *info;

	(void)ac;
	fd = STDIN_FILENO;
	signal(SIGINT, SIG_IGN);
	info = init_sh(argv[0], env);

	if (argv[1])
		fd = open_file(info, argv[1]);
	if (isatty(fd))
	{
		process_input_interactive(info);
	} else
	{
		process_input_noninteractive(info, fd);
	}
	status = info->errno_val;
	destroy_sh(info);
	return (status);
}
