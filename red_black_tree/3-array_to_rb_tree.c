#include "rb_trees.h"

rb_tree_t
*array_to_rb_tree(int *array, size_t size)
{
	rb_tree_t *root = NULL;
	size_t i;

	if (!array || !size)
		return (NULL);

	for (i = 0; i < size; ++i)
		rb_tree_insert(&root, array[i]);

	return (root);
}
