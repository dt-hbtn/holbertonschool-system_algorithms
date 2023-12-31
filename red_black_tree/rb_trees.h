#ifndef SYSTEMALGORITHMS_RBTREES_H
#define SYSTEMALGORITHMS_RBTREES_H

#include <stddef.h>

#define IS_LEFT_CHILD(n) ((n)->parent && ((n) == (n)->parent->left))
#define IS_RIGHT_CHILD(n) ((n)->parent && ((n) == (n)->parent->right))
#define PARENT(n) ((n) ? (n)->parent : NULL)

/**
 * enum rb_color_e - Possible color of a Red-Black tree
 *
 * @RED: 0 -> Red node
 * @BLACK: 1 -> Black node
 */
typedef enum rb_color_e
{
	RED = 0,
	BLACK,
	DOUBLE_BLACK
} rb_color_t;

/**
 * struct rb_tree_s - Red-Black tree node structure
 *
 * @n: Integer stored in the node
 * @parent: Pointer to the parent node
 * @left: Pointer to the left child node
 * @right: Pointer to the right child node
 * @color: Color of the node (RED or BLACK)
 */
typedef struct rb_tree_s
{
	int n;
	rb_color_t color;
	struct rb_tree_s *parent;
	struct rb_tree_s *left;
	struct rb_tree_s *right;
} rb_tree_t;

typedef struct rb_node_family
{
	rb_tree_t *parent, *grandparent, *uncle;
} rb_node_family;

rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color);
int rb_tree_is_valid(const rb_tree_t *tree);
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value);
rb_tree_t *array_to_rb_tree(int *array, size_t size);
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n);
void get_family(rb_node_family *dest, rb_tree_t *node);
void rotate_left(rb_tree_t **root, rb_tree_t *node);
void rotate_right(rb_tree_t **root, rb_tree_t *node);

#endif /* SYSTEMALGORITHMS_RBTREES_H */
