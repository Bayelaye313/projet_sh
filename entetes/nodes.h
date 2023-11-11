#ifndef NODES_H
#define NODES_H

#include <stdlib.h>

/**
 * struct node - a single node in a linked list
 * @var: the name of the node
 * @val: the value associated with this node
 * @next: points to the next node; NULL if there's no next node.
 */
typedef struct node
{
	char *var;
	char *val;
	struct node *next;
} node;

/* Nodes Functions 1 */
node *add_end(node **head, const char *var, const char *val);
node *get_node(node *head, const char *var);
node *set_node(node **head, const char *var, const char *val);
node *set_val(node **head, const char *var, const char *val);

/* Nodes Functions 2 */
char **create_arr(node *head);
bool delete_node(node **head, const char *var);
node *join_arr(char **array);
node *create_env_list(char **env);

#endif
