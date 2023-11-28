#include "huffman.h"

binary_tree_node_t
*huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *pq = NULL;
	binary_tree_node_t *root = NULL;

	if (!data || !freq)
		return (NULL);

	pq = huffman_priority_queue(data, freq, size);

	if (!pq)
		return (NULL);

	while (pq->size > 1)
	{
		if (!huffman_extract_and_insert(pq))
		{
			heap_delete(pq, free_nested_node);
			return (NULL);
		}
	}

	root = heap_extract(pq);
	heap_delete(pq, NULL);
	return (root);
}
