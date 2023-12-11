#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pathfinding.h"

#define VISITED(ctx, v) ((ctx)->visited[(v)->index])

/* STATIC FUNCTIONS */

const vertex_t *graph_backtrack_r(graph_backtrack_ctx_t *ctx,
	const vertex_t *vertex);

graph_backtrack_ctx_t *graph_backtrack_ctx_create(graph_t *graph,
	const vertex_t *target);

/* API IMPLEMENTATION */

/**
 * backtracking_graph - Returns queue_t pointer of path via backtracking
 *
 * @graph: Pointer to graph_t structure
 * @start: Key string of starting vertex
 * @target: Key string of target vertex
 *
 * Return: Pointer to queue_t structure representing the path
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
	vertex_t const *target)
{
	graph_backtrack_ctx_t *ctx = NULL;
	queue_t *path = NULL;

	if (!graph || !start || !target)
		return (NULL);

	ctx = graph_backtrack_ctx_create(graph, target);

	if (!ctx)
		return (NULL);

	if (!graph_backtrack_r(ctx, start))
	{
		queue_delete(ctx->path);
		free(ctx);
		return (NULL);
	}

	path = ctx->path;
	free(ctx);
	return (path);
}

/* STATIC FUNCTIONS */

/**
 * graph_backtrack_r - Recursive graph backtracking function
 *
 * @ctx: Pointer to graph_backtrack_ctx_t structure
 * @vertex: Pointer to current vertex structure
 *
 * Return: Pointer to vertex_t structure if added to path, NULL on failure
 */
const vertex_t *graph_backtrack_r(graph_backtrack_ctx_t *ctx,
	const vertex_t *vertex)
{
	edge_t *edge_pos = NULL;
	int on_target_path = 0;

	if (VISITED(ctx, vertex))
		return (NULL);

	printf("Checking %s\n", vertex->content);

	if (vertex == ctx->target)
	{
		if (!queue_push_front(ctx->path, strdup(vertex->content)))
			return (NULL);

		return (vertex);
	}

	VISITED(ctx, vertex) = 1;

	for (edge_pos = vertex->edges; edge_pos; edge_pos = edge_pos->next)
	{
		if (graph_backtrack_r(ctx, edge_pos->dest))
			on_target_path = 1;
	}

	if (on_target_path)
	{
		if (!queue_push_front(ctx->path, strdup(vertex->content)))
			return (NULL);

		return (vertex);
	}

	return (NULL);
}

/**
 * graph_backtrack_ctx_create - Constructs graph_backtrack_ctx_t structure
 *
 * @graph: Pointer to graph structure
 * @target: Pointer to target vertex
 *
 * Return: Pointer to new graph_backtrack_ctx_t, NULL on failure
 */
graph_backtrack_ctx_t *graph_backtrack_ctx_create(graph_t *graph,
	const vertex_t *target)
{
	graph_backtrack_ctx_t *ctx = NULL;
	queue_t *path = NULL;

	path = queue_create();

	if (!path)
		return (NULL);

	ctx = calloc(1, sizeof(graph_backtrack_ctx_t) + graph->nb_vertices);

	if (!ctx)
	{
		queue_delete(path);
		return (NULL);
	}

	ctx->graph = graph;
	ctx->visited = (unsigned char *)(ctx + 1);
	ctx->target = target;
	ctx->path = path;
	return (ctx);
}
