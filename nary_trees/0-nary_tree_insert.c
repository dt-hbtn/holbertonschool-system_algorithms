#include <stdlib.h>
#include <string.h>
#include "nary_trees.h"

/**
 * nary_tree_insert - Inserts new node into n-ary tree
 *
 * @parent: Pointer to parent node of new node
 * @str: String key assigned to new node
 *
 * Return: Pointer to created node
 */
nary_tree_t *nary_tree_insert(nary_tree_t *parent, const char *str)
{
	nary_tree_t *node = NULL;
	char *str_copy = NULL;

	if (!str)
		return (NULL);

	node = calloc(1, sizeof(nary_tree_t));
	str_copy = strdup(str);

	if (!node || !str_copy)
		goto on_fail;

	node->parent = parent;
	node->content = str_copy;

	if (parent)
	{
		node->next = parent->children;
		parent->children = node;
		++parent->nb_children;
	}

	return (node);

on_fail:
	free(node);
	free(str_copy);
	return (NULL);
}
