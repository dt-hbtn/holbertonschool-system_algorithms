#include <stdlib.h>
#include "huffman.h"

/**
 * huffman_extract_and_insert - Extracts two nodes and inserts their sum node
 *
 * @priority_queue: Pointer to priority queue
 *
 * Return: 1 on success, 0 on failure
 */
int
huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *left = NULL, *right = NULL, *sum_node = NULL;

	if (!priority_queue)
		return (0);

	left = heap_extract(priority_queue);
	right = heap_extract(priority_queue);

	if (!left || !right)
		return (0);

	sum_node = create_sum_node(left, right);

	if (!sum_node)
		return (0);

	return (heap_insert(priority_queue, sum_node) ? 1 : 0);
}

/**
 * create_sum_node - Creates sum node from two leaf nodes
 *
 * @left: Pointer to left child
 * @right: Pointer to right child
 *
 * Return: Pointer to created sum node
 */
binary_tree_node_t
*create_sum_node(binary_tree_node_t *left, binary_tree_node_t *right)
{
	binary_tree_node_t *node = NULL;
	symbol_t *symbol = NULL;
	size_t freq_l, freq_r;

	freq_l = ((symbol_t *)left->data)->freq;
	freq_r = ((symbol_t *)right->data)->freq;

	symbol = symbol_create((char)-1, freq_l + freq_r);

	if (!symbol)
		goto on_failure;

	node = binary_tree_node(NULL, symbol);

	if (!node)
		goto on_failure;

	left->parent = node;
	right->parent = node;
	node->left = left;
	node->right = right;
	return (node);

on_failure:
	free(symbol);
	free(node);
	return (NULL);
}
