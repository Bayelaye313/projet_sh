#include "shell.h"

/**
 * free_list - Frees all nodes and their contents.
 *
 * @head: The head of the linked list.
 *
 * Return: Nothing.
 */
void free_list(node *head)
{
	while (head != NULL)
	{
		node *next = head->next;

		free(head->var);
		free(head->val);
		free(head);
		head = next;
	}
}

/**
 * init_sh - Initializes the shell's state.
 *
 * @prog: The program name.
 * @env: The process' environment variables.
 *
 * Return: The shell's state.
 */
state_t *init_sh(char *prog, char **env)
{
	state_t *info = malloc(sizeof(state_t));

	if (!info)
	{
		perror("Error in malloc");
		exit(EXIT_FAILURE);
	}

	/*Initialize state variables*/
	info->linum = 1;
	info->env = join_arr(env);
	info->prog = prog;
	info->errno_val = 0;
	info->input = NULL;
	info->lines = NULL;
	info->tokens = NULL;
	info->errno_buf = malloc(FRCHAR(12));
	info->pid_buf = make_format("%d", getpid());
	info->toks = NULL;
	info->fd = 0;
	info->buf = NULL;

	return (info);
}

/**
 * destroy_sh - Destroys the shell's state_t.
 *
 * @info: The shell's state_t.
 *
 * Return: Nothing.
 */
void destroy_sh(state_t *info)
{
	if (info)
	{
		/*Free allocated memory*/
		free_list(info->env);
		free(info->input);
		free(info->lines);
		free(info->tokens);
		free(info->toks);
		if (info->fd)
		{
			close(info->fd);
		}
		free(info->pid_buf);
		free(info->errno_buf);
		free(info->buf);
		free(info);
	}
}

/**
 * free_inf - Routine cleanup that frees up memory in the state_t.
 *
 * @info: The shell's state_t.
 *
 * Return: Nothing.
 */
void free_inf(state_t *info)
{
	if (info)
	{
		/*Free allocated memory*/
		free(info->input);
		info->input = NULL;
		if (info->lines)
		{
			free(info->lines);
			info->lines = NULL;
		}
		free(info->toks);
		info->toks = NULL;
		free(info->tokens);
		info->tokens = NULL;
	}
}
