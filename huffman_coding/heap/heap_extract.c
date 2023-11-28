#include <stdlib.h>
#include "heap.h"

static binary_tree_node_t
*get_last_node(const heap_t *heap);

static binary_tree_node_t
*min_child(const heap_t *heap, const binary_tree_node_t *node);

static void
heapify_down(heap_t *heap);

/**
 * heap_extract - Extract from heap
 *
 * @heap: Pointer to heap structure
 *
 * Return: Extracted data pointer
 */
void
*heap_extract(heap_t *heap)
{
	void *result = NULL;
	binary_tree_node_t *last_node = NULL;

	if (!heap || !heap->root || !heap->data_cmp)
		return (NULL);

	result = heap->root->data;

	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
		return (result);
	}

	/* replace root's data with data from last node in heap */
	last_node = get_last_node(heap);
	heap->root->data = last_node->data;

	if (last_node->parent)
	{
		if (heap->size & 1)
			last_node->parent->right = NULL;
		else
			last_node->parent->left = NULL;
	}

	free(last_node);

	/* decrement heap size and heapify downward */
	--heap->size;
	heapify_down(heap);

	/* return original root's data */
	return (result);
}

static binary_tree_node_t
*get_last_node(const heap_t *heap)
{
	binary_tree_node_t *pos = NULL;
	size_t mask;

	/* 2^63 on a 64-bit system */
	mask = 1UL << ((sizeof(size_t) * 8) - 1);

	/* find value of most-significant bit */
	while (!(heap->size & mask))
		mask >>= 1;

	pos = heap->root;

	/* start loop from second-most significant bit */
	/* break when mask reaches 0 */
	for (mask >>= 1; mask; mask >>= 1)
	{
		/* bit is set -> right child */
		/* bit is not set -> left child */
		pos = (heap->size & mask) ? pos->right : pos->left;
	}

	return (pos);
}

static binary_tree_node_t
*min_child(const heap_t *heap, const binary_tree_node_t *node)
{
	int cmp;

	if (node->left && node->right)
	{
		cmp = heap->data_cmp(node->left->data, node->right->data);
		return ((cmp <= 0) ? node->left : node->right);
	}

	/* */
	return (node->left ? node->left : node->right);
}

static void
heapify_down(heap_t *heap)
{
	binary_tree_node_t *parent = NULL, *child = NULL;
	void *tmp_data = NULL;

	parent = heap->root;
	child = min_child(heap, parent);

	while (child && heap->data_cmp(parent->data, child->data) >= 0)
	{
		/* swap parent/child data */
		tmp_data = parent->data;
		parent->data = child->data;
		child->data = tmp_data;
		/* move down the tree */
		parent = child;
		child = min_child(heap, parent);
	}
}
