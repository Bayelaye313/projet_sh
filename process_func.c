#include "shell.h"
/**
 * process_string - Traite une chaîne en appliquant le remplacement de variable et en supprimant les guillemets.
 *
 * @info: Pointeur vers la structure state_t.
 * @str: Chaîne à traiter.
 *
 * Return: Pointeur vers la chaîne modifiée.
 */
char *process_string(state_t *info, char *var)
{
	int len;
	node *n;
	size_t bufsize = 12;

	if (var[0] != '$')
		return (var);

	if (!_strcmp(var, "$$"))
	{
		return (info->pid_buf);
	}
	else if (!_strcmp(var, "$?"))
	{
		len = join_int(&(info->errno_buf), &(bufsize), info->errno_val, 0);
		join_char(&(info->errno_buf), &(bufsize), '\0', len);
		return (info->errno_buf);
	}
	else if (var[0] && !var[1])
		return ("$");
	n = get_node(info->env, var + 1);
	if (!n)
		return ("");
	return (n->val);

}
/**
 * process_tokens - Traite les tokens en appliquant le remplacement de variable et en supprimant les guillemets.
 *
 * @info: Pointeur vers la structure state_t.
 * @tokens: Tableau de tokens à traiter.
 *
 * Cette fonction traite les tokens en appliquant la fonction de remplacement et
 * en supprimant les guillemets doubles.
 */
void process_tokens(state_t *info, char **tokens)
{
	int i, j, k;

	info->tokens = tokens;
	for (i = 0; tokens[i]; i++)
	{
		tokens[i] = process_string(info, tokens[i]);
		for (k = j = 0; tokens[i][k] != '\0'; k++)
		{
			if (tokens[i][k] != '"')
			{
				tokens[i][j++] = tokens[i][k];
			}
		}
		tokens[i][j] = '\0';
	}
}
/**
 * is_logical - Check for logical operators in command tokens.
 * @tokens: Array of command tokens.
 * @index: Starting index to search for logical operators.
 * @next: Pointer to store index of next command after logical operator.
 * Return: 1 for "||", 2 for "&&", 0 if no logical operator found.
 */
int is_logical(char **tokens, int index, int *next)
{
	int i, result;

	for (i = index; tokens[i]; i++)
	{
		if (!_strcmp(tokens[i], "&&") || !_strcmp(tokens[i], "||"))
		{
			result = _strcmp(tokens[i], "&&");
			tokens[i] = NULL;
			*next = i + 1;
			return (result ? 2 : 1);
		}
	}
	*next = index;
	return (0);
}

