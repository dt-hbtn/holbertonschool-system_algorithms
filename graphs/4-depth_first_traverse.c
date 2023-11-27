#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * dfs_ctx_create - Creates depth-first traversal context
 *
 * @n: Number of vertices in graph
 *
 * Return: Pointer to allocated dfs_ctx_t structure
 */
static dfs_ctx_t
*dfs_ctx_create(size_t n);

/**
 * dfs_ctx_delete - Frees dfs_ctx_t resources
 *
 * @ctx: Pointer to dfs_ctx_t structure
 */
static void
dfs_ctx_delete(dfs_ctx_t *ctx);

/**
 * dfs_ctx_pop_vertex - Pops vertex from stack
 *
 * @ctx: Pointer to context struct
 * @dest: Pointer to vertex_tracker_t struct to copy data to
 *
 * Return: `dest` if successful, else NULL
 */
static vertex_tracker_t
*dfs_ctx_pop_vertex(dfs_ctx_t *ctx, vertex_tracker_t *dest);

/**
 * dfs_ctx_push_edges - Pushes unvisited edge dests onto stack
 *
 * @ctx: Pointer to context structure
 * @vertex: Pointer to vertex/depth
 */
static void
dfs_ctx_push_edges(dfs_ctx_t *ctx, vertex_tracker_t *vertex);

/**
 * dfs_ctx_extend_stack - Extends dfs_ctx_t stack capacity
 *
 * @ctx: Pointer to context structure
 *
 * Return: `ctx` if successful, otherwise NULL
 */
static dfs_ctx_t
*dfs_ctx_extend_stack(dfs_ctx_t *ctx);

/**
 * depth_first_traverse - Acts on all graph vertices (depth-first order)
 *
 * @graph: Pointer to graph structure
 * @action: Function pointer that will be called for all vertices
 *
 * Return: The greatest vertex depth or 0UL on failure
 */
size_t
depth_first_traverse(const graph_t *graph, action_t action)
{
	size_t max_depth = 0;
	dfs_ctx_t *ctx = NULL;
	vertex_tracker_t pos;

	if (!graph || !graph->vertices || !action)
		return (0);

	ctx = dfs_ctx_create(graph->nb_vertices);

	if (!ctx)
		return (0);

	/* Push first vertex */
	ctx->stack[++ctx->top].v = graph->vertices;

	while (ctx->top > -1)
	{
		dfs_ctx_pop_vertex(ctx, &pos);

		if (ctx->visited[pos.v->index])
			continue;

		ctx->visited[pos.v->index] = 1;

		if (pos.d > max_depth)
			max_depth = pos.d;

		action(pos.v, pos.d);
		dfs_ctx_push_edges(ctx, &pos);
	}

	dfs_ctx_delete(ctx);
	return (max_depth);
}

/**
 * dfs_ctx_create - Creates depth-first traversal context
 *
 * @n: Number of vertices in graph
 *
 * Return: Pointer to allocated dfs_ctx_t structure
 */
static dfs_ctx_t
*dfs_ctx_create(size_t n)
{
	dfs_ctx_t *ctx = NULL;
	vertex_tracker_t *stack = NULL;
	vertex_t **flip_stack = NULL;
	unsigned char *visited = NULL;

	ctx = calloc(1, sizeof(dfs_ctx_t));
	stack = calloc(n, sizeof(vertex_tracker_t));
	flip_stack = calloc(n, sizeof(vertex_t *));
	visited = calloc(n, sizeof(unsigned char));

	if (!ctx || !stack || !flip_stack || !visited)
		goto alloc_fail;

	ctx->stack = stack;
	ctx->flip_stack = flip_stack;
	ctx->visited = visited;
	ctx->top = -1;
	ctx->stack_capacity = (long)n;

	return (ctx);

alloc_fail:
	free(ctx);
	free(stack);
	free(flip_stack);
	free(visited);
	return (NULL);
}

/**
 * dfs_ctx_delete - Frees dfs_ctx_t resources
 *
 * @ctx: Pointer to dfs_ctx_t structure
 */
static void
dfs_ctx_delete(dfs_ctx_t *ctx)
{
	free(ctx->stack);
	free(ctx->flip_stack);
	free(ctx->visited);
	free(ctx);
}

/**
 * dfs_ctx_pop_vertex - Pops vertex from stack
 *
 * @ctx: Pointer to context struct
 * @dest: Pointer to vertex_tracker_t struct to copy data to
 *
 * Return: `dest` if successful, else NULL
 */
static vertex_tracker_t
*dfs_ctx_pop_vertex(dfs_ctx_t *ctx, vertex_tracker_t *dest)
{
	if (ctx->top < 0)
		return (NULL);

	memcpy(dest, ctx->stack + ctx->top--, sizeof(vertex_tracker_t));
	return (dest);
}

/**
 * dfs_ctx_push_edges - Pushes unvisited edge dests onto stack
 *
 * @ctx: Pointer to context structure
 * @vertex: Pointer to vertex/depth
 */
static void
dfs_ctx_push_edges(dfs_ctx_t *ctx, vertex_tracker_t *vertex)
{
	edge_t *pos = NULL;
	long flip_top = -1;

	for (pos = vertex->v->edges; pos; pos = pos->next)
	{
		if (!ctx->visited[pos->dest->index])
			ctx->flip_stack[++flip_top] = pos->dest;
	}

	if ((ctx->top + flip_top + 1) >= ctx->stack_capacity)
		dfs_ctx_extend_stack(ctx);

	while (flip_top > -1)
	{
		++ctx->top;
		ctx->stack[ctx->top].v = ctx->flip_stack[flip_top--];
		ctx->stack[ctx->top].d = vertex->d + 1;
	}
}

/**
 * dfs_ctx_extend_stack - Extends dfs_ctx_t stack capacity
 *
 * @ctx: Pointer to context structure
 *
 * Return: `ctx` if successful, otherwise NULL
 */
static dfs_ctx_t
*dfs_ctx_extend_stack(dfs_ctx_t *ctx)
{
	vertex_tracker_t *stack = NULL;

	stack = realloc(
		ctx->stack,
		((size_t)ctx->stack_capacity * 2) * sizeof(vertex_tracker_t)
	);

	if (!stack)
		return (NULL);

	ctx->stack = stack;
	ctx->stack_capacity *= 2;
	return (ctx);
}
