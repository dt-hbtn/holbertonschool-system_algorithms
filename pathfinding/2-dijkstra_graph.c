#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pathfinding.h"

#define VISITED(ctx, v) ((ctx)->visited[(v)->index])
#define DISTANCE(ctx, v) ((ctx)->distances[(v)->index].val)
#define NEAREST_PREV(ctx, v) ((ctx)->distances[(v)->index].prev)

#define LOG_VERTEX(ctx, v) printf(\
	"Checking %s, distance from %s is %ld\n",\
	(v)->content,\
	(ctx)->start->content,\
	DISTANCE(ctx, v)\
)

/* STATIC FUNCTIONS */

static int populate_distances(dijkstra_ctx_t *ctx, const vertex_t *vertex);

static const vertex_t *min_unvisited(dijkstra_ctx_t *ctx);

static dijkstra_ctx_t *dijkstra_ctx_create(graph_t *graph,
	const vertex_t *start, const vertex_t *target);

/* API IMPLEMENTATION */

/**
 * dijkstra_graph - Retrieves minimum cost path using Dijkstra's algorithm
 *
 * @graph: Pointer to graph_t structure
 * @start: Pointer to source vertex
 * @target: Pointer to destination vertex
 *
 * Return: Pointer to queue_t structure representing the path
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
	vertex_t const *target)
{
	dijkstra_ctx_t *ctx = NULL;
	queue_t *path = NULL;
	const vertex_t *pos = NULL;

	if (!graph || !start || !target)
		return (NULL);

	ctx = dijkstra_ctx_create(graph, start, target);

	if (!ctx)
		return (NULL);

	if (!populate_distances(ctx, start))
		goto on_fail;

	path = ctx->path;

	for (pos = target; pos; pos = NEAREST_PREV(ctx, pos))
	{
		if (!queue_push_front(path, strdup(pos->content)))
			goto on_fail;
	}

	free(ctx);
	return (path);

on_fail:
	queue_delete(ctx->path);
	free(ctx);
	return (NULL);
}

/* STATIC FUNCTIONS */

/**
 * populate_distances - Finds minimum distances to nodes from start to target
 *
 * @ctx: Pointer to context structure
 * @vertex: Pointer to start vertex
 *
 * Return: 1 on success, 0 on failure
 */
static int populate_distances(dijkstra_ctx_t *ctx, const vertex_t *vertex)
{
	edge_t *edge = NULL;
	long distance;

	for (; vertex; vertex = min_unvisited(ctx))
	{
		LOG_VERTEX(ctx, vertex);

		if (vertex == ctx->target)
			return (1);

		for (edge = vertex->edges; edge; edge = edge->next)
		{
			if (VISITED(ctx, edge->dest))
				continue;

			distance = DISTANCE(ctx, vertex) + (long)edge->weight;

			if (distance < DISTANCE(ctx, edge->dest))
			{
				DISTANCE(ctx, edge->dest) = distance;
				NEAREST_PREV(ctx, edge->dest) = vertex;
			}
		}

		VISITED(ctx, vertex) = 1;
	}

	return (0);
}

/**
 * min_unvisited - Gets the unvisited vertex with minimum distance from start
 *
 * @ctx: Pointer to context structure
 *
 * Return: Pointer to vertex structure, NULL if none available
 */
static const vertex_t *min_unvisited(dijkstra_ctx_t *ctx)
{
	const vertex_t *pos = NULL, *min_vertex = NULL;
	long min_distance = LONG_MAX;

	for (pos = ctx->graph->vertices; pos; pos = pos->next)
	{
		if (VISITED(ctx, pos))
			continue;

		if (DISTANCE(ctx, pos) < min_distance)
		{
			min_distance = DISTANCE(ctx, pos);
			min_vertex = pos;
		}
	}

	return (min_vertex);
}

/**
 * dijkstra_ctx_create - Allocates/initializes dijkstra_ctx_t structure
 *
 * @graph: Pointer to graph structure
 * @start: Pointer to start vertex
 * @target: Pointer to target vertex
 *
 * Return: Pointer to new dijkstra_ctx_t instance, NULL on failure
 */
static dijkstra_ctx_t *dijkstra_ctx_create(graph_t *graph,
	const vertex_t *start, const vertex_t *target)
{
	dijkstra_ctx_t *ctx = NULL;
	queue_t *path = NULL;
	size_t alloc_size, i;

	path = queue_create();

	if (!path)
		return (NULL);

	alloc_size = sizeof(dijkstra_ctx_t);
	alloc_size += graph->nb_vertices * (sizeof(distance_t) + 1);
	ctx = calloc(1, alloc_size);

	if (!ctx)
	{
		queue_delete(path);
		return (NULL);
	}

	ctx->graph = graph;
	ctx->distances = (distance_t *)(ctx + 1);

	for (i = 0; i < graph->nb_vertices; ++i)
		ctx->distances[i].val = LONG_MAX;

	ctx->distances[start->index].val = 0L;
	ctx->visited = (unsigned char *)(ctx->distances + graph->nb_vertices);
	ctx->start = start;
	ctx->target = target;
	ctx->path = path;
	return (ctx);
}
