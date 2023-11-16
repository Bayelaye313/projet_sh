#include "shell.h"
#define HOME "HOME"
#define PATH "PATH"

/**
 * my_env - Print all shell environment variables
 *
 * @info: Pointer to the shell's state_t structure
 * @args: Unused array of command line arguments
 *
 * Return: Always returns 0
 */
int my_env(state_t *info, char **args)
{
	/* Use environ to access environment variables */
	char **env = environ;

	(void)info;
	(void)args;

	/* Loop through the environment variables and print them */
	while (*env != NULL)
	{
		myprintf("%s\n", *env);
		env++;
	}
	return (0);
}

/**
 * _setenv - Set or modify an environment variable
 *
 * @info: Pointer to the shell's state_t structure
 * @args: Array of command line arguments
 *
 * Return: 0 on success, 1 if VARIABLE is missing, 2 if VALUE is not supplied,
 *         3 if an error occurs during node insertion
 */
int _setenv(state_t *info, char **args)
{
	char *name, *value;
	node *env_node;

	if (args[1] == NULL || args[2] == NULL || args[3] != NULL)
	{
		print_error("setenv: Incorrect usage. Use setenv VARIABLE VALUE\n");
		return (1);
	}

	if (!_isalpha(args[1][0]))
	{
		print_error("setenv: Variable name must start with a letter\n");
		return (2);
	}

	name = args[1];
	value = args[2];

	/*Check if the variable already exists*/
	env_node = get_node(info->env, name);

	if (env_node)
	{
		/*Variable exists, update its value*/
		free(env_node->val);
		env_node->val = _strdup(value);
	}
	else
	{
		/*Variable does not exist, create a new one*/
		set_node(&(info->env), name, value);
	}

	return (0);
}

/**
 * _unsetenv - Unset an environment variable
 *
 * @info: Pointer to the shell's state_t structure
 * @args: Array of command line arguments
 *
 * Return: 0 on success, 1 if VARIABLE is missing,
 *         2 if VARIABLE does not exist,
 *         3 if an error occurs during node deletion
 */
int _unsetenv(state_t *info, char **args)
{
	node *env_node;
	const char *target_var;

	if (args[0] == NULL)
	{
		print_error("unsetenv: Variable name missing\n");
		return (1);
	}

	target_var = args[0];

	/*Check if the variable is a protected variable (HOME, PATH)*/
	if (!_strcmp(target_var, HOME) || !_strcmp(target_var, PATH))
	{
		print_error("unsetenv: Cannot unset protected variable\n");
		return (1);
	}

	/*Check if the variable exists*/
	env_node = get_node(info->env, target_var);

	if (!env_node)
	{
		print_error("unsetenv: Variable does not exist\n");
		return (2);
	}

	/*Delete the variable*/
	if (!delete_node(&(info->env), target_var))
	{
		perror("unsetenv");
		return (3);
	}

	return (0);
}
