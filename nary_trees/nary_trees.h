#ifndef SYSTEMALGORITHMS_NARYTREES_H
#define SYSTEMALGORITHMS_NARYTREES_H

#include <stddef.h>

/**
 * struct nary_tree_s - N-ary tree node structure
 *
 * @content: Content of the node
 * @parent: Pointer to the parent node
 * @nb_children: Number of children
 * @children: Pointer to the head node of the children linked list
 * @next: Pointer to the next child in the parent's children linked list
 */
typedef struct nary_tree_s
{
	char *content;
	struct nary_tree_s *parent;
	size_t nb_children;
	struct nary_tree_s *children;
	struct nary_tree_s *next;
} nary_tree_t;

typedef void (*action_t)(const nary_tree_t *node, size_t depth);

/* TASK 0 */
nary_tree_t *nary_tree_insert(nary_tree_t *parent, const char *str);

/* TASK 1 */
void nary_tree_delete(nary_tree_t *tree);

/* TASK 2 */
size_t nary_tree_traverse(const nary_tree_t *root, action_t action);

/* TASK 3 */
size_t nary_tree_diameter(const nary_tree_t *root);

/* TASK 4 */
int path_exists(const nary_tree_t *root, const char * const path);

#endif /* SYSTEMALGORITHMS_NARYTREES_H */
