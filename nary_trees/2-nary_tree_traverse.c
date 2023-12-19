#include "nary_trees.h"

static size_t nary_tree_traverse_r(const nary_tree_t *node, size_t depth,
	action_t action);

/**
 * nary_tree_traverse - Performs arbitrary action on all nodes of n-ary tree
 *
 * @root: Pointer to root of n-ary tree
 * @action: Pointer to function performed on each node
 *
 * Return: Max depth reached in traversal
 */
size_t nary_tree_traverse(const nary_tree_t *root, action_t action)
{
	if (!root || !action)
		return (0UL);

	return (nary_tree_traverse_r(root, 0UL, action));
}

static size_t nary_tree_traverse_r(const nary_tree_t *node, size_t depth,
	action_t action)
{
	size_t tmp, max_depth = depth;
	const nary_tree_t *child_pos = NULL;

	action(node, depth);

	child_pos = node->children;

	while (child_pos)
	{
		tmp = nary_tree_traverse_r(child_pos, depth + 1, action);

		if (tmp > max_depth)
			max_depth = tmp;

		child_pos = child_pos->next;
	}

	return (max_depth);
}
