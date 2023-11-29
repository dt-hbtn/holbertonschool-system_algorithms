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

/**
 * struct code_node_s - Stack node for tracking Huffman codes in tree
 *
 * @node: Pointer to tree node
 * @depth: Depth in tree
 * @path_flag: 0 if left child, 1 if right child
 */
typedef struct code_node_s
{
	binary_tree_node_t *node;
	long depth : 63;
	unsigned char path_flag : 1;
} code_node_t;

symbol_t
*symbol_create(char data, size_t freq);

heap_t
*huffman_priority_queue(char *data, size_t *freq, size_t size);

int
huffman_extract_and_insert(heap_t *priority_queue);

binary_tree_node_t
*huffman_tree(char *data, size_t *freq, size_t size);

int
huffman_codes(char *data, size_t *freq, size_t size);

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
