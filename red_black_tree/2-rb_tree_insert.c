#include "rb_trees.h"

#define UNCLE_COLOR(f) ((f).uncle ? (f).uncle->color : BLACK)

static rb_tree_t
*bst_insert(rb_tree_t *root, rb_tree_t *parent, int value, rb_tree_t **node);

static void
fix_insert(rb_tree_t **root, rb_tree_t *node);

static void
swap_colors(rb_tree_t *a, rb_tree_t *b);

static void
recolor_family(rb_tree_t *root, rb_node_family *family);

static void
rotate_family(rb_tree_t **root, rb_tree_t *node, rb_node_family *family);

/**
 * 
 */
rb_tree_t
*rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new_node = NULL;

	if (!tree)
		return (NULL);

	if (!*tree)
	{
		*tree = rb_tree_node(NULL, value, BLACK);
		return (*tree);
	}

	bst_insert(*tree, NULL, value, &new_node);

	if (new_node)
		fix_insert(tree, new_node);

	return (new_node);
}

static rb_tree_t
*bst_insert(rb_tree_t *root, rb_tree_t *parent, int value, rb_tree_t **node)
{
	if (!root)
	{
		*node = rb_tree_node(parent, value, RED);
		return (*node);
	}

	if (value < root->n)
		root->left = bst_insert(root->left, root, value, node);
	else if (value > root->n)
		root->right = bst_insert(root->right, root, value, node);
	else
		*node = NULL;

	return (root);
}

static void
fix_insert(rb_tree_t **root, rb_tree_t *node)
{
	rb_node_family family;

	get_family(&family, node);

	while (family.parent && family.grandparent)
	{
		if (family.parent->color != RED)
		{
			node = family.grandparent;
			get_family(&family, node);
			continue;
		}

		if (UNCLE_COLOR(family) == RED)
			recolor_family(*root, &family);
		else
			rotate_family(root, node, &family);

		node = family.grandparent;
		get_family(&family, node);
	}

	*root = family.parent ? family.parent : node;
}

static void
swap_colors(rb_tree_t *a, rb_tree_t *b)
{
	rb_color_t tmp;

	tmp = a->color;
	a->color = b->color;
	b->color = tmp;
}

static void
recolor_family(rb_tree_t *root, rb_node_family *family)
{
	family->parent->color = BLACK;
	family->uncle->color = BLACK;

	if (family->grandparent != root)
		family->grandparent->color = RED;
}

static void
rotate_family(rb_tree_t **root, rb_tree_t *node, rb_node_family *family)
{
	if (IS_LEFT_CHILD(family->parent) && IS_LEFT_CHILD(node))
	{
		rotate_right(root, family->grandparent);
		swap_colors(family->grandparent, family->parent);
	}
	if (IS_LEFT_CHILD(family->parent) && IS_RIGHT_CHILD(node))
	{
		rotate_left(root, family->parent);
		rotate_right(root, family->grandparent);
		swap_colors(family->grandparent, node);
	}
	if (IS_RIGHT_CHILD(family->parent) && IS_RIGHT_CHILD(node))
	{
		rotate_left(root, family->grandparent);
		swap_colors(family->grandparent, family->parent);
	}
	if (IS_RIGHT_CHILD(family->parent) && IS_LEFT_CHILD(node))
	{
		rotate_right(root, family->parent);
		rotate_left(root, family->grandparent);
		swap_colors(family->grandparent, node);
	}
}
