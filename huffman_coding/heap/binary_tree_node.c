#include <stdlib.h>
#include "heap.h"

/**
 * binary_tree_node - Allocates new binary-tree node structure
 *
 * @parent: Pointer to parent node
 * @data: Data pointer (key)
 *
 * Return: Pointer to allocated node structure
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *node = NULL;

	if (!data)
		return (NULL);

	node = calloc(1, sizeof(binary_tree_node_t));

	if (!node)
		return (NULL);

	node->parent = parent;
	node->data = data;
	return (node);
}
