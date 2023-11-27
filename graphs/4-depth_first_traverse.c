#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * dfs_ctx_s - Depth-first traversal context
 *
 * @stack: Stack of vertices/depths
 * @flip_stack: Intermediary stack used to push edge dests in opposite order
 * @visited: Array of visited flags corresponding to vertex indices
 * @top: Top index of `stack` 
 */
typedef struct dfs_ctx_s
{
	vertex_tracker_t *stack;
	vertex_t **flip_stack;
	unsigned char *visited;
	long top;
} dfs_ctx_t;

/**
 * dfs_ctx_create - Creates depth-first traversal context
 *
 * @nb_vertices: Number of vertices in graph
 *
 * Return: Pointer to allocated dfs_ctx_t structure
 */
static dfs_ctx_t
*dfs_ctx_create(size_t nb_vertices);

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
	ctx->stack[ctx->top].d = 0;

	while (ctx->top > -1)
	{
		if (!dfs_ctx_pop_vertex(ctx, &pos))
			break;

		if (pos.d > max_depth)
			max_depth = pos.d;

		action(pos.v, pos.d);
		dfs_ctx_push_edges(ctx, &pos);
	}

	free(ctx);
	return (max_depth);
}

/**
 * dfs_ctx_create - Creates depth-first traversal context
 *
 * @nb_vertices: Number of vertices in graph
 *
 * Return: Pointer to allocated dfs_ctx_t structure
 */
static dfs_ctx_t
*dfs_ctx_create(size_t n)
{
	dfs_ctx_t *ctx = NULL;
	size_t block_size;

	/* Space for the dfs_ctx_t struct itself */
	block_size = sizeof(dfs_ctx_t);
	/* Space for stack */
	block_size += n * sizeof(vertex_tracker_t);
	/* Space for flip stack */
	block_size += n * sizeof(vertex_t *);
	/* Space for visited flags */
	block_size += n * sizeof(unsigned char);

	ctx = calloc(1, block_size);

	if (!ctx)
		return (NULL);

	ctx->stack = (vertex_tracker_t *)(ctx + 1);
	ctx->flip_stack = (vertex_t **)(ctx->stack + n);
	ctx->visited = (unsigned char *)(ctx->flip_stack + n);
	ctx->top = -1;

	return (ctx);
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
	while (ctx->top >= 0 && ctx->visited[ctx->stack[ctx->top].v->index])
		--ctx->top;

	if (ctx->top < 0)
		return (NULL);

	memcpy(dest, ctx->stack + ctx->top--, sizeof(vertex_tracker_t));

	ctx->visited[dest->v->index] = 1;
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

	while (flip_top > -1)
	{
		++ctx->top;
		ctx->stack[ctx->top].v = ctx->flip_stack[flip_top--];
		ctx->stack[ctx->top].d = vertex->d + 1;
	}
}
