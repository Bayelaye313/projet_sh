#include "shell.h"
/**
 * exec_builtin - execute a builtin command
 *
 * @info: the shell's state
 * @arguments: command line arguments passed to the shell
 *
 * Return: true(1) if a command was found else false(0)
 */
bool exec_builtin(state_t *info, char **arguments)
{
	int i, status;
	char *command, **args;
	builtin_t builtins[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", my_cd},
		{ NULL, NULL }
	};

	command = arguments[0];
	args = arguments + 1;

	for (i = 0; builtins[i].name; i++)
	{
		if (!_strcmp(builtins[i].name, command))
		{
			status = builtins[i].handler(info, args);
			info->errno_val = status;
			return (true);
		}
	}
	return (false);
}

/**
 * run_exec - Executes a command with its arguments.
 *
 * @info: Pointer to the shell's state_t.
 * @arguments: Array of arguments to be passed.
 *
 * Return: True if execution was successful, false otherwise.
 */
int run_exec(state_t *info, char **arguments)
{
	char *path, **env;
	bool free_path = false;
	int status, i;
	struct stat filestat;

	path = arguments[0];

	if (!is_cmd(path))
	{
		path = get_absolute_path(path,
			set_val(&(info->env), "PATH", "")->val);
		if (!path)
			return (false);
		free_path = true;
	}
	else if (access(path, F_OK) == -1)
		return (false);

	stat(path, &filestat);

	if (access(path, X_OK) == -1 || S_ISREG(filestat.st_mode) == 0)
	{
		print_permission_denied(info, arguments);
		info->errno_val = 126;
	}
	else
	{
		env = create_arr(info->env);
		status = execute(path, arguments, env);
		for (i = 0; env[i]; i++)
			free(env[i]);
		free(env);
		info->errno_val = status;
	}
	if (free_path)
		free(path);

	return (true);
}
