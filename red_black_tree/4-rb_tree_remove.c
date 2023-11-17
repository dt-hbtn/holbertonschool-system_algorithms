#include <stdio.h>
#include <stdlib.h>
#include "rb_trees.h"

// Helper function to fix violations after removing a node
void fix_remove(rb_tree_t **tree, rb_tree_t *x, rb_tree_t *x_parent)
{
	while (x != *tree && (x == NULL || x->color == BLACK))
	{
		if (x == x_parent->left)
		{
			rb_tree_t *w = x_parent->right;

			if (w != NULL && w->color == RED)
			{
				w->color = BLACK;
				x_parent->color = RED;
				left_rotate(tree, x_parent);
				w = x_parent->right;
			}

			if ((w->left == NULL || w->left->color == BLACK) &&
			    (w->right == NULL || w->right->color == BLACK))
			{
				w->color = RED;
				x = x_parent;
				x_parent = x_parent->parent;
			}
			else
			{
				if (w->right == NULL || w->right->color == BLACK)
				{
					if (w->left != NULL)
					{
						w->left->color = BLACK;
					}
					w->color = RED;
					right_rotate(tree, w);
					w = x_parent->right;
				}

				w->color = x_parent->color;
				x_parent->color = BLACK;

				if (w->right != NULL)
				{
					w->right->color = BLACK;
				}

				left_rotate(tree, x_parent);
				x = *tree;
			}
		}
		else
		{
			rb_tree_t *w = x_parent->left;

			if (w != NULL && w->color == RED)
			{
				w->color = BLACK;
				x_parent->color = RED;
				right_rotate(tree, x_parent);
				w = x_parent->left;
			}

			if ((w->right == NULL || w->right->color == BLACK) &&
			    (w->left == NULL || w->left->color == BLACK))
			{
				w->color = RED;
				x = x_parent;
				x_parent = x_parent->parent;
			}
			else
			{
				if (w->left == NULL || w->left->color == BLACK)
				{
					if (w->right != NULL)
					{
						w->right->color = BLACK;
					}
					w->color = RED;
					left_rotate(tree, w);
					w = x_parent->left;
				}

				w->color = x_parent->color;
				x_parent->color = BLACK;

				if (w->left != NULL)
				{
					w->left->color = BLACK;
				}

				right_rotate(tree, x_parent);
				x = *tree;
			}
		}
	}

	if (x != NULL)
	{
		x->color = BLACK;
	}
}

// Helper function to find the minimum value node in a subtree
rb_tree_t *tree_min(rb_tree_t *node)
{
	while (node != NULL && node->left != NULL)
	{
		node = node->left;
	}
	return node;
}

// Helper function to replace a node with another node
void transplant(rb_tree_t **tree, rb_tree_t *u, rb_tree_t *v)
{
	if (u->parent == NULL)
	{
		*tree = v; // If u is the root, update the root of the tree
	}
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}

	if (v != NULL)
	{
		v->parent = u->parent;
	}
}

// Helper function to fix the tree after deletion
void delete_fixup(rb_tree_t **tree, rb_tree_t *x, rb_tree_t *x_parent)
{
	rb_tree_t *w;

	while ((x == NULL || x->color == BLACK) && x != *tree)
	{
		if (x == x_parent->left)
		{
			w = x_parent->right;

			if (w->color == RED)
			{
				w->color = BLACK;
				x_parent->color = RED;
				left_rotate(tree, x_parent);
				w = x_parent->right;
			}

			if ((w->left == NULL || w->left->color == BLACK) &&
			    (w->right == NULL || w->right->color == BLACK))
			{
				w->color = RED;
				x = x_parent;
				x_parent = x_parent->parent;
			}
			else
			{
				if (w->right == NULL || w->right->color == BLACK)
				{
					if (w->left != NULL)
					{
						w->left->color = BLACK;
					}
					w->color = RED;
					right_rotate(tree, w);
					w = x_parent->right;
				}

				w->color = x_parent->color;
				x_parent->color = BLACK;

				if (w->right != NULL)
				{
					w->right->color = BLACK;
				}

				left_rotate(tree, x_parent);
				x = *tree;
			}
		}
		else
		{
			w = x_parent->left;

			if (w->color == RED)
			{
				w->color = BLACK;
				x_parent->color = RED;
				right_rotate(tree, x_parent);
				w = x_parent->left;
			}

			if ((w->right == NULL || w->right->color == BLACK) &&
			    (w->left == NULL || w->left->color == BLACK))
			{
				w->color = RED;
				x = x_parent;
				x_parent = x_parent->parent;
			}
			else
			{
				if (w->left == NULL || w->left->color == BLACK)
				{
					if (w->right != NULL)
					{
						w->right->color = BLACK;
					}
					w->color = RED;
					left_rotate(tree, w);
					w = x_parent->left;
				}

				w->color = x_parent->color;
				x_parent->color = BLACK;

				if (w->left != NULL)
				{
					w->left->color = BLACK;
				}

				right_rotate(tree, x_parent);
				x = *tree;
			}
		}
	}

	if (x != NULL)
	{
		x->color = BLACK;
	}
}

// Helper function to remove a node from the Red-Black tree
rb_tree_t *rb_tree_remove_node(rb_tree_t *tree, rb_tree_t *z)
{
	rb_tree_t *y = z;
	rb_tree_t *x, *x_parent;

	if (z->left == NULL)
	{
		x = z->right;
		x_parent = z->parent;
		transplant(&tree, z, z->right);
	}
	else if (z->right == NULL)
	{
		x = z->left;
		x_parent = z->parent;
		transplant(&tree, z, z->left);
	}
	else
	{
		y = tree_min(z->right);
		x = y->right;
		x_parent = y;

		if (y->parent == z)
		{
			x_parent = y;
		}
		else
		{
			transplant(&tree, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		transplant(&tree, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	if (y->color == BLACK)
	{
		delete_fixup(&tree, x, x_parent);
	}

	return tree;
}

// Main function to remove a value from the Red-Black tree
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	rb_tree_t *z = root;

	// Find the node to be removed
	while (z != NULL)
	{
		if (n == z->n)
		{
			root = rb_tree_remove_node(root, z);
			return root;
		}
		else if (n < z->n)
		{
			z = z->left;
		}
		else
		{
			z = z->right;
		}
	}

	return root;
}
