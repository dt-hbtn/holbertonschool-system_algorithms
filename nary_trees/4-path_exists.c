#include <string.h>
#include "nary_trees.h"

static const nary_tree_t *find_sibling(const nary_tree_t *node,
	const char *content);

/**
 * path_exists - Checks n-ary tree for path
 *
 * @root: Pointer to root of n-ary tree
 * @path: Pointer to NULL-terminated array of strings
 *
 * Return: 1: path found, 0: path not found
 */

int path_exists(const nary_tree_t *root, const char * const *path)
{
	if (!root || !path)
		return (0);

	for (; *path; ++path)
	{
		root = find_sibling(root, *path);

		if (!root)
			return (0);

		root = root->children;
	}

	return (1);
}

static const nary_tree_t *find_sibling(const nary_tree_t *node,
	const char *content)
{
	for (; node; node = node->next)
		if (!strcmp(node->content, content))
			return (node);

	return (NULL);
}
