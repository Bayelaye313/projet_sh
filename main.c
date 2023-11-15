#include "shell.h"
void sigint_handler(int signum)
{
    (void)signum;
    myprintf("\n"); /*Imprimer une nouvelle ligne après Ctrl+C*/
    prompt();       /*Afficher le prompt après Ctrl+C*/
}
/**
 * comment - Identifies a comment in command line
 *
 * @string: the command line string
 * Return: Nothing. It is void
 */
void comment(char *string)
{
	int j;

	if (string == NULL)
		return;
	for (j = 0; string[j]; j++)
		if (string[j] == '#')
			if (j == 0 || string[j - 1] == ' ')
			{
				string[j] = '\0';
				break;
			}
}

/**
 * process_input - Processes input and executes corresponding commands.
 *
 * @info: Pointer to state_t_t structure.
 * @input: Input string to process.
 */
/*void process_input(state_t_t *info, char *input)
{
	int l;
	char **toks;

	info->input = input;
	handle_hashtag(input);
	toks = split_line_line(input, ";", 0);
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
}*/

/**
 * choose_mode - Chooses the mode of the shell based on command-line arguments.
 *
 * @info: Pointer to the shell's state_t_t.
 * @argv: Array of command-line argument strings.
 *
 * Return: The file descriptor for input.
 */
/*int choose_mode(state_t_t *info, char **argv)
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
	return (fd);
}
*/
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
 * interactive - runs the shell in interactive mode
 *
 * @info: the shell's state_t
 *
 * Return: always 0
 */
int interactive(state_t *info)
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
 * non_interactive - run shell in non-interactive mode
 * all commands would be read from a file.
 *
 * @info: shell's state_t
 * @fd: descriptor of file to read from
 *
 * Return: always 0
 */
int non_interactive(state_t *info, int fd)
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
int main(int ac, char **av, char **env)
{
	int status;
	state_t *info;
	int fd;

	(void)ac;
	fd = STDIN_FILENO;
	signal(SIGINT, SIG_IGN);
	info = init_sh(av[0], env);

	if (av[1])
		fd = open_file(info, av[1]);
	if (isatty(fd))
		interactive(info);
	else
		non_interactive(info, fd);
	status = info->errno_val;
	destroy_sh(info);
	return (status);
}
