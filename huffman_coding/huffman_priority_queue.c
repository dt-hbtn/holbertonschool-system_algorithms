#include <stdlib.h>
#include "huffman.h"

static binary_tree_node_t
*create_nested_node(char data, size_t freq);

static int
cmp_nested_nodes(void *a, void *b);

static void
free_nested_node(void *node);

/**
 * huffman_priority_queue - Creates Huffman priority queue from chars/freqs
 *
 * @data: Array of characters constituting the text's alphabet
 * @freq: Array of character frequencies (parallel to `data`)
 * @size: Length of the `data` and `freq` arrays
 *
 * Return: Pointer to created Huffman priority queue, NULL on failure
 */
heap_t
*huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap = NULL;
	binary_tree_node_t *nested_data = NULL;
	size_t i;

	if (!data || !freq)
		return (NULL);

	heap = heap_create(cmp_nested_nodes);

	if (!heap)
		return (NULL);

	for (i = 0; i < size; ++i)
	{
		nested_data = create_nested_node(data[i], freq[i]);

		if (!nested_data || !heap_insert(heap, nested_data))
		{
			heap_delete(heap, free_nested_node);
			return (NULL);
		}
	}

	return (heap);
}

static binary_tree_node_t
*create_nested_node(char data, size_t freq)
{
	binary_tree_node_t *nested_node = NULL;
	symbol_t *symbol = NULL;

	symbol = symbol_create(data, freq);

	if (!symbol)
		goto on_failure;

	nested_node = binary_tree_node(NULL, symbol);

	if (!nested_node)
		goto on_failure;

	return (nested_node);

on_failure:
	free(symbol);
	free(nested_node);
	return (NULL);
}

static int
cmp_nested_nodes(void *a, void *b)
{
	binary_tree_node_t *node_a, *node_b;
	long freq_a, freq_b;

	node_a = (binary_tree_node_t *)a;
	node_b = (binary_tree_node_t *)b;
	freq_a = (long)((symbol_t *)node_a->data)->freq;
	freq_b = (long)((symbol_t *)node_b->data)->freq;

	return ((int)(freq_a - freq_b));
}

static void
free_nested_node(void *node)
{
	if (!node)
		return;

	free(((binary_tree_node_t *)node)->data); /* symbol data */
	free(node);
}
