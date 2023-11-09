#include "shell.h"
/**
 * runcommand - Exécute une seule commande.
 *
 * @info: Pointeur vers la structure state_t.
 * @command: Le nom de la commande et les arguments.
 *
 * Retourne : Rien.
 */
void runcommand(state_t *info, char **command)
{
	bool command_found;
	int i;

	if (!command[0])
		return;
	for (i = 0; command[i]; i++)
	{
		rm_quotes(command[i]);
	}
	command_found = exec_builtin(info, command);
	if (!command_found)
		command_found = run_exec(info, command);
	if (!command_found)
	{
		print_command_not_found(info, command[0]);
		info->errno_val = EKEYEXPIRED;
	}
}
/**
 * exec_line - Executes a command specified by a given input line.
 *
 * @info: Pointer to the shell's state_t structure.
 * @line: String containing the command to be executed.
 *
 * Return: 0 on successful execution, or an error code otherwise.
 */
int exec_line(state_t *info, char *line)
{
	char **tokens = split_line(line, "\t ", 0), **command;
	int index = 0, next, op, i;

	if (!tokens)
		return (0);
	info->tokens = tokens;
	for (i = 0; tokens[i]; i++)
		tokens[i] = process_string(info, tokens[i]);
	command = tokens + index;
	op = is_logical(tokens, index, &next);
	if (!command[0] && op)
	{
		fprinterr(make_format("%s: %d: Syntax error: \"%s\" unexpected\n",
			info->prog, info->linum, op == 1 ? "&&" : "||"));
		info->tokens = (free(info->tokens), NULL);
		info->errno_val = 2;
		return (0);
	}
	runcommand(info, command);
	index = next;
	while (op)
	{
		if ((op == 2 && !info->errno_val) ||
			(op == 1 && info->errno_val))
		{
			op = is_logical(tokens, index, &next);
			index = next;
			continue;
		}
		command = tokens + index;
		op = is_logical(tokens, index, &next);
		runcommand(info, command);
		index = next;
	}
	free(info->tokens);
	info->tokens = NULL;
	return (0);
}

/**
 * execute - execute a program in a child process
 * @argv: path of the program to execute
 * @args: command line arguments to pass to the program
 * @env: the environment variables for this process
 * Return: the exit status of the child process
 */
int execute(const char *argv, char *args[], char *env[])
{
	pid_t pid_child;
	int status;

	if (argv == NULL || args == NULL || env == NULL)
	{
		my_fprintf(stderr, "Invalid arguments\n");
		return (-1);
	}
	pid_child = fork();
	if (pid_child == -1)
	{
		perror("Error:");
		return (1);
	}
	if (pid_child == 0)
	{
		if (execve(argv, args, env) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);

		}
	}
	else
	{
		if (waitpid(pid_child, &status, 0) == -1)
		{
			perror("waitpid failed");
			return (-1);
		}

		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	return (status);
}
