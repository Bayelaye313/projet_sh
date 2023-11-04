#include "shell.h"
#define BUFSIZE 1024
typedef struct alias_node
{
    char *name;
    char *value;
    struct alias_node *next;
} alias_node;

void print_alias(state_t *info)
{
    alias_node *current = info->aliase;
    char buffer[BUFSIZE];

    while (current)
    {
        memset(buffer, 0, BUFSIZE);
        strcat(buffer, current->name);
        strcat(buffer, "='");
        strcat(buffer, current->value);
        strcat(buffer, "'\n");

        write(STDOUT_FILENO, buffer, strlen(buffer));

        current = current->next;
    }
}
