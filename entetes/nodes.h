#ifndef NODES_H
#define NODES_H

#include <stdlib.h>

/**
 * struct node - this represents a single node in a
 * linked list
 * @var: the name of the node
 * @val: the value associated with this node
 * @next: a pointer the next node, this would be null if theres no next node.
 */
typedef struct node
{
	char *var;
	char *val;
	struct node *next;
} node;

/*nodes functions1*/
node *add_end(node **head, const char *var, const char *val);
node *get_node(node *head, const char *var);
node *set_node(node **head, const char *var, const char *val);
node *set_val(node **head, const char *var, const char *val);

/*nodes functions2*/
char **create_arr(node *head);
bool delete_node(node **head, const char *var);
node *join_arr(char **array);
node *create_env_list(char **env);

#endif
