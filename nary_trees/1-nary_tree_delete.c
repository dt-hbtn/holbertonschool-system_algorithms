#include <stdlib.h>
#include "nary_trees.h"

/**
 * nary_tree_delete - Recursively frees an n-ary tree
 *
 * @tree: Pointer to n-ary tree
 */
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *tmp = NULL;

	if (!tree)
		return;

	while (tree->children)
	{
		tmp = tree->children->next;
		nary_tree_delete(tree->children);
		tree->children = tmp;
	}

	free(tree->content);
	free(tree);
}
