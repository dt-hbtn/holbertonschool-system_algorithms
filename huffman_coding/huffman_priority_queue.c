#include <stdlib.h>
#include "huffman.h"

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
		nested_data = nested_leaf_node(data[i], freq[i]);

		if (!nested_data || !heap_insert(heap, nested_data))
		{
			heap_delete(heap, free_nested_node);
			return (NULL);
		}
	}

	return (heap);
}

/**
 * nested_leaf_node - Creates nested binary-tree node containing symbol info
 *
 * @data: Character
 * @freq: Frequency of character in text
 *
 * Return: Pointer to allocated nested node
 */
binary_tree_node_t
*nested_leaf_node(char data, size_t freq)
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

/**
 * cmp_nested_nodes - Comparator for nested nodes
 *
 * @a: Pointer to first node
 * @b: Pointer to second node
 *
 * Return: 0 if equal, <0 if less-than, >0 if greater-than
 */
int
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

/**
 * free_nested_node - Frees node and symbol data
 *
 * @node: Pointer to node
 */
void
free_nested_node(void *node)
{
	if (!node)
		return;

	free(((binary_tree_node_t *)node)->data); /* symbol data */
	free(node);
}
