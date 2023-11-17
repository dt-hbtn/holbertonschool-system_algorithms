#include <stdlib.h>
#include "rb_trees.h"

rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *node = NULL;

	node = calloc(1, sizeof(rb_tree_t));

	if (!node)
		return (NULL);

	node->n = value;
	node->color = color;
	node->parent = parent;

	return (node);
}

void get_family(rb_node_family *dest, rb_tree_t *node)
{
	dest->grandparent = NULL;
	dest->uncle = NULL;
	dest->parent = PARENT(node);

	if (!dest->parent)
		return;

	dest->grandparent = PARENT(dest->parent);

	if (IS_LEFT_CHILD(dest->parent))
		dest->uncle = dest->grandparent->right;
	else if (IS_RIGHT_CHILD(dest->parent))
		dest->uncle = dest->grandparent->left;
	else
		dest->uncle = NULL;
}

void rotate_left(rb_tree_t **root, rb_tree_t *node)
{
	rb_tree_t *new_root = NULL, *parent = NULL;

	if (!node || !(new_root = node->right))
		return;

	parent = node->parent;
	node->right = new_root->left;

	if (node->right)
		node->right->parent = node;

	new_root->left = node;
	new_root->parent = parent;

	if (IS_LEFT_CHILD(node))
		parent->left = new_root;
	else if (IS_RIGHT_CHILD(node))
		parent->right = new_root;

	node->parent = new_root;

	if (node == *root)
		*root = new_root;
}

void rotate_right(rb_tree_t **root, rb_tree_t *node)
{
	rb_tree_t *new_root = NULL, *parent = NULL;

	if (!node || !(new_root = node->left))
		return;

	parent = node->parent;
	node->left = new_root->right;

	if (node->left)
		node->left->parent = node;

	new_root->right = node;
	new_root->parent = parent;

	if (parent && parent->left == node)
		parent->left = new_root;
	else if (parent && parent->right == node)
		parent->right = new_root;

	node->parent = new_root;

	if (node == *root)
		*root = new_root;
}
