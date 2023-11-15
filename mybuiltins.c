#include "shell.h"
#define HOME "HOME"
#define PATH "PATH"
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
/**
 * cd_to_home - Change directory to the user's home directory
 *
 * @info: Pointer to the shell's state_t structure (unused)
 *
 * Return: 0 on success, non-zero on failure
 */
int cd_to_home(state_t *info __attribute__((unused)))
{
	char *home = get_node(info->env, "HOME")->val;

	if (!home)
		return (0);
	return (chdir(home));
}
/**
 * cd_to_previous - Change directory to the previous directory (OLDPWD)
 *
 * @info: Pointer to the shell's state_t structure (unused)
 *
 * Return: 0 on success, non-zero on failure
 */
int cd_to_previous(state_t *info __attribute__((unused)))
{
	char *oldpwd = get_node(info->env, "OLDPWD")->val;

	if (!oldpwd)
		return (1);
	myprintf(oldpwd);
	myprintf("\n");
	return (chdir(oldpwd));
}
/**
 * cd_illegal_option - Handle illegal option for cd command
 *
 * @info: Pointer to the shell's state_t structure
 * @option: Illegal option character
 *
 * Return: 2 (error code for illegal option)
 */
int cd_illegal_option(state_t *info, char option)
{
	print_cd_illegal_option(info, option);
	return (2);
}
int is_valid_directory(const char *path)
{
    struct stat dir;
    return stat(path, &dir) == 0 && S_ISDIR(dir.st_mode) && dir.st_mode & S_IXUSR;
}

/**
 * my_cd - Change the current directory
 *
 * @info: Pointer to the shell's state_t structure
 * @args: Command line arguments
 *
 * Return: 0 on success, 2 on failure
 */
int my_cd(state_t *info, char **args)
{
    char *path = args[0];
    char *pwd = get_node(info->env, "PWD")->val;
    char *home = get_node(info->env, "HOME")->val;
    char *oldpwd = get_node(info->env, "OLDPWD")->val;
    char *new_pwd;

    if (!path || !_strcmp(path, "~"))
    {
        if (!home)
            return (0);
        path = home;
    }
    else if (path && !_strcmp(path, "-"))
    {
        path = oldpwd;
        myprintf(path);
        myprintf("\n");
        return (cd_to_previous(info));
    }
    else if (path && path[0] == '-')
    {
        return (cd_illegal_option(info, path[1]));
    }

    if (is_valid_directory(path))
    {
        if (chdir(path) == 0)
        {
            set_node(&(info->env), "OLDPWD", pwd);
            new_pwd = getcwd(NULL, 0);
            set_node(&(info->env), "PWD", new_pwd);
            free(new_pwd);
            return (0);
        }
    }

    print_cd_cant_change(info, path);
    return (2);
}

