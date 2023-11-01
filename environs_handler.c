#include "shell.h"
#define HOME "HOME"
#define PATH "PATH"

/**
 * my_env - Prints out all shell environment variables
 *
 * @info: Pointer to the shell's state_t structure
 * @args: Array of command line arguments (unused)
 *
 * Return: Always returns 0
 */
int my_env(state_t *info, char **args)
{
	/*Using environ to access environment variables*/
	char **env = environ;

	(void)info;
	(void)args;
	/*Loop through the environment variables and print them*/
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
	switch (args[0] ? 1 : 0)
	{
		case 0:
			print_error("Usage: setenv VARIABLE VALUE\n");
			return (1);
		case 1:
			break;
	}
	switch (args[1] ? 1 : 0)
	{
		case 0:
			print_error("setenv: VALUE not supplied\n");
			return (2);
		case 1:
			break;
	}
	if (!_strcmp(args[1], PATH) && !args[1][0])
		return (0);
	if (!set_node(&(info->env), args[0], args[1]))
	{
		perror("setenv");
		return (3);
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
 * 2 if VARIABLE does not exist,
 * 3 if an error occurs during node deletion
 */
int _unsetenv(state_t *info, char **args)
{
	const char *target_var;
	node *env_node;

	if (!args[0])
	{
		print_error("unsetenv: VARIABLE missing\n");
		return (1);
	}
	target_var = args[0];
	if (!_strcmp(target_var, HOME) || !_strcmp(target_var, PATH))
		return (0);
	env_node = get_node(info->env, target_var);
	if (!env_node)
	{
		print_unsetenv_error(target_var);
		return (2);
	}
	if (!delete_node(&(info->env), target_var))
	{
		perror("unsetenv");
		return (3);
	}
	return (0);
}
