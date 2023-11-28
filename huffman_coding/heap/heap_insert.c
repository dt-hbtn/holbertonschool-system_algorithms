#include "heap.h"

static binary_tree_node_t
*get_parent_of_new(const heap_t *heap);

static binary_tree_node_t
*heapify_up(heap_t *heap, binary_tree_node_t *node);

/**
 * heap_insert - Inserts data into the heap
 *
 * @heap: Pointer to heap structure
 * @data: Pointer to new data
 *
 * Return: Pointer to the inserted node
 */
binary_tree_node_t
*heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new_node = NULL, *parent = NULL;

	if (!heap || !heap->data_cmp || !data)
		return (NULL);

	if (!heap->root)
	{
		new_node = binary_tree_node(NULL, data);

		if (!new_node)
			return (NULL);

		heap->root = new_node;
		heap->size = 1;
		return (new_node);
	}

	parent = get_parent_of_new(heap);
	new_node = binary_tree_node(parent, data);

	if (!new_node)
		return (NULL);

	if (heap->size & 1)
		parent->left = new_node;
	else
		parent->right = new_node;

	++heap->size;
	return (heapify_up(heap, new_node));
}

static binary_tree_node_t
*get_parent_of_new(const heap_t *heap)
{
	binary_tree_node_t *pos = NULL;
	size_t new_size, mask;

	/* size + 1 because we want the parent of the NEW node */
	new_size = heap->size + 1;
	/* 2^63 on a 64-bit system */
	mask = 1UL << ((sizeof(size_t) * 8) - 1);

	/* find value of most-significant bit */
	while (!(new_size & mask))
		mask >>= 1;

	pos = heap->root;

	/* start loop from second-most significant bit */
	/* break before least significant bit */
	for (mask >>= 1; mask > 1; mask >>= 1)
	{
		/* bit is set -> right child */
		/* bit is not set -> left child */
		pos = (new_size & mask) ? pos->right : pos->left;
	}

	return (pos);
}

static binary_tree_node_t
*heapify_up(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *parent = node->parent;
	void *tmp_data = NULL;

	/* continue while parent's data is greater than node's data */
	while (parent && heap->data_cmp(parent, node) > 0)
	{
		/* swap node/parent data */
		tmp_data = parent->data;
		parent->data = node->data;
		node->data = tmp_data;
		/* move up the tree */
		node = parent;
		parent = node->parent;
	}

	return (node);
}
