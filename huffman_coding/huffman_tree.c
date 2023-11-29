#include <stdlib.h>
#include "_huffman.h"

/**
 * huffman_tree - Generates a Huffman tree
 *
 * @data: Character-alphabet array
 * @freq: Corresponding character frequencies (parallel to `data`)
 * @size: Number of characters in alphabet
 *
 * Return: Pointer to root of Huffman tree. NULL on failure
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
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

/**
 * delete_huffman_tree - Iteratively deletes Huffman tree
 *
 * @root: Pointer to root of Huffman tree
 * @n: Number of characters in alphabet
 */
void delete_huffman_tree(binary_tree_node_t *root, size_t n)
{
	binary_tree_node_t **stack = NULL, *pos = NULL;
	long top = -1;

	stack = calloc(MAX_HUFFMAN_NODES(n), sizeof(binary_tree_node_t *));

	if (!stack)
		return;

	stack[++top] = root;

	while (top > -1)
	{
		pos = stack[top--];

		if (pos->right)
			stack[++top] = pos->right;

		if (pos->left)
			stack[++top] = pos->left;

		free(pos->data);
		free(pos);
	}

	free(stack);
}
