#include <stdbool.h>
#include "rb_trees.h"

bool is_valid_rb_tree(const rb_tree_t *node, int black_count, int *path_black_count)
{
	// Base case: NIL nodes are black
	if (node == NULL)
	{
		*path_black_count = 1;
		return true;
	}

	// Check for consecutive red nodes
	if (node->color == RED)
	{
		if ((node->left != NULL && node->left->color == RED) ||
		    (node->right != NULL && node->right->color == RED))
		{
			return false;
		}
	}

	// Recursively check left and right subtrees
	int left_count, right_count;
	bool left_valid = is_valid_rb_tree(node->left, black_count, &left_count);
	bool right_valid = is_valid_rb_tree(node->right, black_count, &right_count);

	// Check if the current node has the same number of black nodes on every path
	if (left_count != right_count)
	{
		return false;
	}

	// Update the path black count for the parent node
	*path_black_count = left_count + (node->color == BLACK);

	// Check the root node's color
	if (node->parent == NULL && node->color != BLACK)
	{
		return false;
	}

	return left_valid && right_valid;
}

int rb_tree_is_valid(const rb_tree_t *tree)
{
	int path_black_count;
	return is_valid_rb_tree(tree, 0, &path_black_count);
}
