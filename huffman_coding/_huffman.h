#ifndef SYSTEMALGORITHMS_HUFFMANCODING_HUFFMAN_DETAIL_H
#define SYSTEMALGORITHMS_HUFFMANCODING_HUFFMAN_DETAIL_H

#include "huffman.h"

#define MAX_HUFFMAN_NODES(n) ((2 * (n)) - 1)
#define CODE_STACK_EMPTY(s) ((s)->top < 0)
#define HUFFMAN_NODE_CHAR(n) (((symbol_t *)(n)->data)->data)
#define HUFFMAN_NODE_FREQ(n) (((symbol_t *)(n)->data)->freq)
#define IS_LEAF_CHAR(c) ((int)(c) != -1)

/**
 * struct code_node_s - Stack node for Huffman-code enumeration from tree
 *
 * @node: Pointer to tree node
 * @depth: Depth in tree
 * @path_flag: 0 if left child, 1 if right child
 */
typedef struct code_node_s
{
	binary_tree_node_t *node;
	signed depth : 31;
	unsigned path_flag : 1;
} code_node_t;

/**
 * struct code_stack_s - Stack for Huffman-code enumeration from tree
 *
 * @data: Pointer to first node in stack array
 * @top: Index of stack top
 */
typedef struct code_stack_s
{
	code_node_t *data;
	int top;
} code_stack_t;

typedef void (*leaf_action_t)(const char c, const char *code,
	const int code_len, void *args);

binary_tree_node_t *nested_leaf_node(char data, size_t freq);

binary_tree_node_t *create_sum_node(binary_tree_node_t *left,
	binary_tree_node_t *right);

int cmp_nested_nodes(void *a, void *b);

void free_nested_node(void *node);

void delete_huffman_tree(binary_tree_node_t *root, size_t n);

code_stack_t *code_stack_create(size_t n);

void code_stack_push(code_stack_t *stack, binary_tree_node_t *node,
	int depth, unsigned char path_flag);

void code_stack_pop(code_stack_t *stack, binary_tree_node_t **node,
	int *depth, unsigned char *path_flag);

void traverse_codes(binary_tree_node_t *tree, code_stack_t *stack,
	leaf_action_t leaf_action, void *args);

#endif /* SYSTEMALGORITHMS_HUFFMANCODING_HUFFMAN_DETAIL_H */
