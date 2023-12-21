#include <string.h>
#include "nary_trees.h"

#define CONTENT_MATCHES(n, c) (!strcmp((n)->content, (c)))

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
		/* search current level for path component */
		for (; root; root = root->next)
			if (CONTENT_MATCHES(root, *path))
				break;

		/* current path component not found */
		if (!root)
			return (0);

		/* move to next level */
		root = root->children;
	}

	return (1); /* all path items found in correct order */
}
