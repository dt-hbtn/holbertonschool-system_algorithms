#ifndef SYSTEMALGORITHMS_HUFFMANCODING_HUFFMAN_H
#define SYSTEMALGORITHMS_HUFFMANCODING_HUFFMAN_H

#include <stddef.h>
#include "heap.h"

/**
 * struct symbol_s - Stores a char and its associated frequency
 *
 * @data: The character
 * @freq: The associated frequency
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;

symbol_t
*symbol_create(char data, size_t freq);

heap_t
*huffman_priority_queue(char *data, size_t *freq, size_t size);

int
huffman_extract_and_insert(heap_t *priority_queue);

/* Helper functions */

binary_tree_node_t
*nested_leaf_node(char data, size_t freq);

binary_tree_node_t
*create_sum_node(binary_tree_node_t *left, binary_tree_node_t *right);

int
cmp_nested_nodes(void *a, void *b);

void
free_nested_node(void *node);

#endif /* SYSTEMALGORITHMS_HUFFMANCODING_HUFFMAN_H */
