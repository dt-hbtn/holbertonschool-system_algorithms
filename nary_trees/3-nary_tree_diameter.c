#include "nary_trees.h"

#define GOLD(a) ((a)[0])
#define SILVER(a) ((a)[1])

#define UPDATE_MAX_DIAMETER(n, a, v)		\
	do {					\
		(v) = nary_tree_diameter((n));	\
		if ((v) > GOLD(a))		\
			GOLD(a) = (v);		\
	} while (0)

#define UPDATE_MAX_HEIGHTS(n, a, v)		\
	do {					\
		(v) = nary_tree_height((n));	\
		if ((v) > GOLD(a))		\
		{				\
			SILVER(a) = GOLD(a);	\
			GOLD(a) = (v);		\
		}				\
		else if ((v) > SILVER(a))	\
		{				\
			SILVER(a) = (v);	\
		}				\
	} while (0)

#define MAX_PATH(a) (GOLD(a) + SILVER(a) + 1)

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
	size_t maxes[2] = { 0UL, 0UL }, max_path, current;
	const nary_tree_t *child = NULL;

	if (!root)
		return (0UL);

	for (child = root->children; child; child = child->next)
		UPDATE_MAX_HEIGHTS(child, maxes, current);

	max_path = MAX_PATH(maxes);
	GOLD(maxes) = 0UL;

	for (child = root->children; child; child = child->next)
		UPDATE_MAX_DIAMETER(child, maxes, current);

	return (max_path > GOLD(maxes) ? max_path : GOLD(maxes));
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
	size_t max_height = 0, child_height;

	for (node = node->children; node; node = node->next)
	{
		child_height = nary_tree_height(node);

		if (child_height > max_height)
			max_height = child_height;
	}

	return (max_height + 1);
}
