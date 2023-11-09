#include "shell.h"
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
#include "shell.h"

/**
 * choose_mode - Chooses the mode of the shell based on command-line arguments.
 *
 * @info: Pointer to the shell's state_t.
 * @argv: Array of command-line argument strings.
 *
 * Return: The file descriptor for input.
 */
int choose_mode(state_t *info, char **argv)
{
	int fd = STDIN_FILENO;

	if (argv[1])
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_cant_open(info, argv[1]);
				destroy_sh(info);
				exit(127);
			}
		}
	}
	signal(SIGINT, SIG_IGN);
	return (fd);
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
	int status, fd;
	state_t *info;

	(void)argc;
	info = init_sh(argv[0], env);

	fd = choose_mode(info, argv);

	if (isatty(fd))
	{
		char *input;

		while (1)
		{
			prompt();
			input = _getline(STDIN_FILENO);
			if (!input)
			{
				myprintf("\n");
				break;
			}
			process_input(info, input);
		}
	}
	else
	{
		char *input = _getline(fd);

		if (input)
		{
			process_input(info, input);
			free(input);
		}
	}
	status = info->errno_val;
	destroy_sh(info);
	return (status);
}
