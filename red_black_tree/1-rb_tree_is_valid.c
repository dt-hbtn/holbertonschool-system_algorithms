#include <stdbool.h>
#include "rb_trees.h"

bool
is_valid_rb_tree(const rb_tree_t *node, int black_count, int *path_black_count)
{
	if (node == NULL)
	{
		*path_black_count = 1;
		return true;
	}

	if (node->color == RED)
	{
		if ((node->left != NULL && node->left->color == RED) ||
		    (node->right != NULL && node->right->color == RED))
		{
			return false;
		}
	}

	int left_count, right_count;
	bool left_valid = is_valid_rb_tree(node->left, black_count, &left_count);
	bool right_valid = is_valid_rb_tree(node->right, black_count, &right_count);

	if (left_count != right_count)
	{
		return false;
	}

	*path_black_count = left_count + (node->color == BLACK);

	if (node->parent == NULL && node->color != BLACK)
	{
		return false;
	}

	return left_valid && right_valid;
}

int
rb_tree_is_valid(const rb_tree_t *tree)
{
	int path_black_count;
	return is_valid_rb_tree(tree, 0, &path_black_count);
}
