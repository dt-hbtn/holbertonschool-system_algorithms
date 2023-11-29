#include <stdlib.h>
#include "heap.h"

/**
 * heap_delete - Frees resources held by heap_t structure
 *
 * @heap: Pointer to heap structure
 * @free_data: Optional function to free `data` members on nodes
 */
void heap_delete(heap_t *heap, free_data_t free_data)
{
	binary_tree_node_t **stack = NULL, *pos = NULL;
	long top = -1;

	if (!heap)
		return;

	stack = calloc(heap->size, sizeof(binary_tree_node_t *));

	if (!stack)
		return;

	if (heap->root)
		stack[++top] = heap->root;

	while (top > -1)
	{
		pos = stack[top--];

		if (pos->right)
			stack[++top] = pos->right;

		if (pos->left)
			stack[++top] = pos->left;

		if (free_data)
			free_data(pos->data);

		free(pos);
	}

	heap->root = NULL;
	heap->size = 0;
	heap->data_cmp = NULL;

	free(stack);
	free(heap);
}
