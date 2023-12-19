#include "nary_trees.h"

static size_t nary_tree_height(const nary_tree_t *node);

/**
 * nary_tree_diameter - Calculates diameter of n-ary tree
 *
 * @root: Pointer to n-ary tree structure
 *
 * Return: Diameter of n-ary tree
 */
size_t nary_tree_diameter(const nary_tree_t *root)
{
	size_t max1 = 0UL, max2 = 0UL, max_diam = 0UL, tmp;
	const nary_tree_t *child = NULL;

	if (!root)
		return (0UL);

	for (child = root->children; child; child = child->next)
	{
		tmp = nary_tree_height(child);

		if (tmp > max1)
		{
			max2 = max1;
			max1 = tmp;
		}
		else if (tmp > max2)
		{
			max2 = tmp;
		}
	}

	for (child = root->children; child; child = child->next)
	{
		tmp = nary_tree_diameter(child);

		if (tmp > max_diam)
			max_diam = tmp;
	}

	tmp = max1 + max2 + 1;
	return (tmp > max_diam ? tmp : max_diam);
}

/**
 * nary_tree_height - Calculates height of n-ary tree
 *
 * @node: Pointer to n-ary tree structure
 *
 * Return: Height of n-ary tree
 */
static size_t nary_tree_height(const nary_tree_t *node)
{
	size_t height = 0, tmp;

	for (node = node->children; node; node = node->next)
	{
		tmp = nary_tree_height(node);

		if (tmp > height)
			height = tmp;
	}

	return (height + 1);
}
