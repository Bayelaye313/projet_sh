#include "shell.h"
/**
 * my_exit - Exit the shell
 *
 * @info: Pointer to the shell's state_t structure
 * @args: Array of command line arguments
 *
 * Return: 0 on success, 2 if the argument is not a valid number
 */
int my_exit(state_t *info, char **args)
{
	int status = 0;
	char *arg = args[0];
	int i = 0;

	if (arg == NULL)
	{
		status = info->errno_val;
		destroy_sh(info);
		exit(status);
	}
	while (arg[i] != '\0')
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
		{
			print_exit_error(info, arg);
			return (2); /* Code d'erreur pour une conversion invalide*/
		}
		i++;
	}
	status = _atoi(arg);
	destroy_sh(info);
	exit(status);
}
