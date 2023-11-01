#include "shell.h"
/**
 * is_cmd - Checks if a string contains a forward slash (/).
 * @s: The input string to be checked.
 *
 * Return: True if a forward slash is found, otherwise false.
 */
bool is_cmd(const char *s)
{
    while (*s)
    {
        if (*s++ == '/')
            return true;
    }
    return (false);
}
/**
 * get_absolute_path - searches through $PATH to find a command
 *
 * @command: name of the command
 * @PATH: a string containing directories in which to search
 * for the command. The directories should be delimited by :
 *
 * Return: a pointer to the path of the command if found, otherwise NULL
 */
char *get_absolute_path(const char *command, const char *PATH)
{
    char **dirs, *dirname, *PATHCPY, *cmd;
    DIR *dir;
    struct dirent *node;
    int i, j, index;

    cmd = NULL;
    PATHCPY = _strdup(PATH);
    dirs = split_line(PATHCPY, ":", 0);
    if (!dirs)
    {
        free(PATHCPY);
        return (NULL);
    }
    for (i = 0; dirs[i]; i++)
    {
        dirname = dirs[i];
        dir = opendir(dirname);
        if (!dir)
            continue;
        node = readdir(dir);
        while (node != NULL)
        {
            if (_strcmp(command, node->d_name) == 0)
            {
                int baselen = _strlen(dirname);
                int childlen = _strlen(node->d_name);
                bool has_sep = (dirname[baselen - 1] == '/' || node->d_name[0] == '/');

                cmd = malloc(baselen + childlen + (has_sep ? 1 : 2));
                if (cmd == NULL)
                {
                    closedir(dir);
                    free(PATHCPY);
                    free(dirs);
                    return (NULL);
                }

                index = 0;
                for (j = 0; j < baselen; j++)
                    cmd[index++] = dirname[j];
                if (!has_sep)
                    cmd[index++] = '/';
                for (j = 0; j < childlen; j++)
                    cmd[index++] = node->d_name[j];
                cmd[index] = '\0';

                closedir(dir);
                free(PATHCPY);
                free(dirs);
                return cmd;
            }
            node = readdir(dir);
        }
        closedir(dir);
    }
    free(PATHCPY);
    free(dirs);
    return (cmd);
}