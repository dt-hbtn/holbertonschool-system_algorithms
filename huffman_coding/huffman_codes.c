#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

static void code_stack_push(code_node_t *stack, long *top,
	binary_tree_node_t *node, long depth, unsigned char path_flag);

static void code_stack_pop(code_node_t *stack, long *top,
	binary_tree_node_t **node, long *depth, unsigned char *path_flag);

static void
delete_tree(binary_tree_node_t *root, size_t n);

int
huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *tree = NULL, *pos = NULL;
	code_node_t *stack = NULL;
	long top = -1, depth;
	char c, code_buf[256] = { '\0' };
	unsigned char path_flag;

	if (!data || !freq)
		return (0);

	tree = huffman_tree(data, freq, size);

	if (!tree)
		return (0);

	stack = calloc((2 * size) - 1, sizeof(code_node_t));

	if (!stack)
	{
		/* free tree first */
		return (0);
	}

	code_stack_push(stack, &top, tree, 0, 0);

	while (top > -1)
	{
		code_stack_pop(stack, &top, &pos, &depth, &path_flag);
		c = ((symbol_t *)pos->data)->data;

		code_buf[depth] = path_flag ? '1' : '0';

		if (c != (char)-1)
		{
			printf("%c: %.*s\n", c, (int)depth, code_buf + 1);
		}
		else
		{
			++depth;
			code_stack_push(stack, &top, pos->right, depth, 1);
			code_stack_push(stack, &top, pos->left, depth, 0);
		}
	}

	free(stack);
	delete_tree(tree, size);
	return (1);
}

static void code_stack_push(code_node_t *stack, long *top,
	binary_tree_node_t *node, long depth, unsigned char path_flag)
{
	++(*top);
	stack[*top].node = node;
	stack[*top].depth = depth;
	stack[*top].path_flag = path_flag;
}

static void code_stack_pop(code_node_t *stack, long *top,
	binary_tree_node_t **node, long *depth, unsigned char *path_flag)
{
	*node = stack[*top].node;
	*depth = stack[*top].depth;
	*path_flag = stack[*top].path_flag;
	--(*top);
}

static void
delete_tree(binary_tree_node_t *root, size_t n)
{
	binary_tree_node_t **stack = NULL, *pos = NULL;
	long top = -1;

	stack = calloc((n * 2) - 1, sizeof(binary_tree_node_t *));

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
