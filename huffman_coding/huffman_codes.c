#include <stdio.h>
#include <stdlib.h>
#include "_huffman.h"

static void print_code(const char c, const char *code,
	const int code_len, void *args);

/**
 * huffman_codes - Generates Huffman tree and prints all codes
 *
 * @data: Character-alphabet array
 * @freq: Corresponding character frequencies (parallel to `data`)
 * @size: Number of characters in alphabet
 *
 * Return: 1 for success, 0 for failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *tree = NULL;
	code_stack_t *stack = NULL;

	if (!data || !freq)
		return (0);

	/* generate Huffman tree */
	tree = huffman_tree(data, freq, size);

	if (!tree)
		return (0);

	/* allocate stack for code enumeration */
	stack = code_stack_create(size);

	if (!stack)
	{
		delete_huffman_tree(tree, size);
		return (0);
	}

	/* traverse the tree and call `print_code` on all leaf nodes */
	traverse_codes(tree, stack, print_code, NULL);

	/* free stack and Huffman tree */
	free(stack);
	delete_huffman_tree(tree, size);
	return (1);
}

/**
 * code_stack_create - Allocates a stack for Huffman code enumeration
 *
 * @n: Number of characters in alphabet
 *
 * Return: Pointer to allocated code_stack_t structure, NULL on failure
 */
code_stack_t *code_stack_create(size_t n)
{
	code_stack_t *stack = NULL;
	size_t mem_size;

	mem_size = sizeof(code_stack_t);
	mem_size += (MAX_HUFFMAN_NODES(n) * sizeof(code_node_t));
	stack = calloc(1, mem_size);

	if (!stack)
		return (NULL);

	stack->data = (code_node_t *)(stack + 1);
	stack->top = -1;
	return (stack);
}

/**
 * code_stack_push - Pushes node and metadata onto a code_stack_t
 *
 * @stack: Pointer to code_stack_t structure
 * @node: Node to push
 * @depth: Tree depth of `node`
 * @path_flag: 0 if `node` is left child, 1 if right child
 */
void code_stack_push(code_stack_t *stack, binary_tree_node_t *node,
	int depth, unsigned char path_flag)
{
	++stack->top;
	stack->data[stack->top].node = node;
	stack->data[stack->top].depth = depth;
	stack->data[stack->top].path_flag = path_flag;
}

/**
 * code_stack_pop - Pops node and metadata from code_stack_t
 *
 * @stack: Pointer to code_stack_t structure
 * @node: Destination address for popped node pointer
 * @depth: Destination address for `depth`
 * @path_flag: Destination address for `path_flag`
 */
void code_stack_pop(code_stack_t *stack, binary_tree_node_t **node,
	int *depth, unsigned char *path_flag)
{
	*node = stack->data[stack->top].node;
	*depth = stack->data[stack->top].depth;
	*path_flag = stack->data[stack->top].path_flag;
	--stack->top;
}

/**
 * traverse_codes - Traverse Huffman tree (DFS) and performs action on leaves
 *
 * @tree: Pointer to root of Huffman tree
 * @stack: Pointer to code_stack_t structure
 * @leaf_action: Function to call on all leaf nodes
 * @args: Pointer to extended arguments (passed to `leaf_action`)
 */
void traverse_codes(binary_tree_node_t *tree, code_stack_t *stack,
	leaf_action_t leaf_action, void *args)
{
	char c, code_buf[256] = { '\0' };
	binary_tree_node_t *pos = NULL;
	int depth;
	unsigned char path_flag;

	code_stack_push(stack, tree, 0, 0);

	while (!CODE_STACK_EMPTY(stack))
	{
		code_stack_pop(stack, &pos, &depth, &path_flag);
		c = HUFFMAN_NODE_CHAR(pos);
		code_buf[depth] = path_flag ? '1' : '0';

		if (IS_LEAF_CHAR(c))
		{
			leaf_action(c, code_buf + 1, depth, args);
		}
		else
		{
			code_stack_push(stack, pos->right, depth + 1, 1);
			code_stack_push(stack, pos->left, depth + 1, 0);
		}
	}
}

/**
 * print_code - Prints character and its corresponding Huffman code
 *
 * @c: Plain character
 * @code: Pointer to start of code string
 * @code_len: Length of code string (null termination not guaranteed)
 * @args: NULL (unused)
 */
static void print_code(const char c, const char *code,
	const int code_len, void *args)
{
	printf("%c: %.*s\n", c, code_len, code);
}
