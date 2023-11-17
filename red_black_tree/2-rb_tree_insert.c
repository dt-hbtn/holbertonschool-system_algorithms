#include <stdlib.h>
#include "rb_trees.h"

#define UNCLE_COLOR(f) ((f).uncle ? (f).uncle->color : BLACK)

static rb_tree_t *bst_insert(rb_tree_t *node, rb_tree_t *parent, int value, rb_tree_t **new_node)
{
	if (!node)
	{
		*new_node = rb_tree_node(parent, value, RED);
		return (*new_node);
	}

	if (value < node->n)
	{
		node->left = bst_insert(node->left, node, value, new_node);
	}
	else if (value > node->n)
	{
		node->right = bst_insert(node->right, node, value, new_node);
	}
	else
	{
		*new_node = NULL;
	}

	return (node);
}

/* static void swap_colors(rb_tree_t *a, rb_tree_t *b)
{
	rb_color_t tmp;

	tmp = a->color;
	a->color = b->color;
	b->color = tmp;
} */

static void fix_insert(rb_tree_t **root, rb_tree_t *node)
{
	rb_node_family family;

	get_family(&family, node);

	/* if (!family.parent)
	{
		node->color = BLACK;
		*root = node;
		return;
	} */

	while (family.parent && family.grandparent)
	{
		if (family.parent->color == RED && UNCLE_COLOR(family) == RED)
		{
			family.parent->color = BLACK;
			family.uncle->color = BLACK;
			family.grandparent->color = RED;
		}
		else if (family.parent->color == RED)
		{
			if (IS_LEFT_CHILD(family.parent) && IS_LEFT_CHILD(node))
			{
				family.parent->color = BLACK;
				family.grandparent->color = RED;
				rotate_right(root, family.grandparent);
				/* swap_colors(family.grandparent, family.parent); */

			}
			if (IS_LEFT_CHILD(family.parent) && IS_RIGHT_CHILD(node))
			{
				node->color = BLACK;
				family.grandparent->color = RED;
				rotate_left(root, family.parent);
				rotate_right(root, family.grandparent);
				/* swap_colors(family.grandparent, family.parent); */
			}
			if (IS_RIGHT_CHILD(family.parent) && IS_RIGHT_CHILD(node))
			{
				family.parent->color = BLACK;
				family.grandparent->color = RED;
				rotate_left(root, family.grandparent);
				/* swap_colors(family.grandparent, family.parent); */
			}
			if (IS_RIGHT_CHILD(family.parent) && IS_LEFT_CHILD(node))
			{
				node->color = BLACK;
				family.grandparent->color = RED;
				rotate_right(root, family.parent);
				rotate_left(root, family.grandparent);
				/* swap_colors(family.grandparent, family.parent); */
			}
		}

		node = family.grandparent;
		get_family(&family, node);
	}

	if (family.parent)
	{
		if (family.parent->color == RED)
			node->color = BLACK;
		
		*root = family.parent;
	}
	else
	{
		*root = node;
	}

	(*root)->color = BLACK;
}

rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
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


/* 
// Helper function to fix violations after inserting a node
void fix_insert(rb_tree_t **tree, rb_tree_t *new_node)
{
	while (new_node != NULL && new_node->parent != NULL && new_node->parent->color == RED)
	{
		if (new_node->parent == new_node->parent->parent->left)
		{
			rb_tree_t *uncle = new_node->parent->parent->right;

			if (uncle != NULL && uncle->color == RED)
			{
				new_node->parent->color = BLACK;
				uncle->color = BLACK;
				new_node->parent->parent->color = RED;
				new_node = new_node->parent->parent;
			}
			else
			{
				if (new_node == new_node->parent->right)
				{
					new_node = new_node->parent;
					left_rotate(tree, new_node);
				}

				new_node->parent->color = BLACK;
				new_node->parent->parent->color = RED;
				right_rotate(tree, new_node->parent->parent);
			}
		}
		else
		{
			rb_tree_t *uncle = new_node->parent->parent->left;

			if (uncle != NULL && uncle->color == RED)
			{
				new_node->parent->color = BLACK;
				uncle->color = BLACK;
				new_node->parent->parent->color = RED;
				new_node = new_node->parent->parent;
			}
			else
			{
				if (new_node == new_node->parent->left)
				{
					new_node = new_node->parent;
					right_rotate(tree, new_node);
				}

				new_node->parent->color = BLACK;
				new_node->parent->parent->color = RED;
				left_rotate(tree, new_node->parent->parent);
			}
		}
	}

	(*tree)->color = BLACK;
}

// Helper function to insert a value into the Red-Black tree
rb_tree_t *rb_tree_insert_value(rb_tree_t **tree, rb_tree_t *parent, int value)
{
	if (*tree == NULL)
	{
		*tree = rb_tree_node(parent, value, RED);
		if (*tree == NULL)
		{
			return NULL; // Memory allocation failed
		}
		fix_insert(tree, *tree);
		return *tree;
	}

	if (value < (*tree)->n)
	{
		return rb_tree_insert_value(&(*tree)->left, *tree, value);
	}
	else if (value > (*tree)->n)
	{
		return rb_tree_insert_value(&(*tree)->right, *tree, value);
	}

	return NULL; // Value already exists in the tree
}

// Main function to insert a value into the Red-Black tree
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new_node = rb_tree_insert_value(tree, NULL, value);
	if (new_node != NULL)
	{
		new_node->color = BLACK; // Root must be black
	}
	return new_node;
}
 */