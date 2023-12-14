#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pathfinding.h"

#define INFINITY (UINT_MAX >> 1) /* max for 31-bit unsigned */
#define IN_QUEUE(ctx, v) ((ctx)->entries[(v)->index].in_queue)
#define DISTANCE(ctx, v) ((ctx)->entries[(v)->index].distance)
#define NEAREST_PREV(ctx, v) ((ctx)->entries[(v)->index].prev)
#define HEAP_LEFT(i) (((i) << 1) + 1)
#define HEAP_RIGHT(i) (((i) << 1) + 1)
#define HEAP_PARENT(i) (((i) - 1) >> 1)

#define LOG_VERTEX(ctx, v) printf(\
	"Checking %s, distance from %s is %u\n",\
	(v)->content,\
	(ctx)->start->content,\
	DISTANCE(ctx, v)\
)

/* STATIC FUNCTIONS */

static int populate_distances(dijkstra_ctx_t *ctx);

static const vertex_t *pq_insert(dijkstra_ctx_t *ctx, const vertex_t *vertex);

static const vertex_t *pq_extract(dijkstra_ctx_t *ctx);

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

	if (!populate_distances(ctx))
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
 *
 * Return: 1 on success, 0 on failure
 */
static int populate_distances(dijkstra_ctx_t *ctx)
{
	const vertex_t *pos = NULL;
	edge_t *edge = NULL;
	unsigned int dist;

	pq_insert(ctx, ctx->start);

	while (ctx->pq_size)
	{
		pos = pq_extract(ctx);

		if (!pos)
			return (0);

		LOG_VERTEX(ctx, pos);

		if (pos == ctx->target)
			return (1);

		for (edge = pos->edges; edge; edge = edge->next)
		{
			dist = DISTANCE(ctx, pos) + (unsigned int)edge->weight;

			if (dist < DISTANCE(ctx, edge->dest))
			{
				DISTANCE(ctx, edge->dest) = dist;
				NEAREST_PREV(ctx, edge->dest) = pos;

				if (!IN_QUEUE(ctx, edge->dest))
					pq_insert(ctx, edge->dest);
			}
		}
	}

	return (0);
}

/**
 * pq_insert - Inserts vertex into priority queue
 *
 * @ctx: Pointer to Dijkstra's algorithm context structure
 * @vertex: Pointer to vertex being inserted
 *
 * Return: Pointer to inserted vertex, NULL on failure
 */
static const vertex_t *pq_insert(dijkstra_ctx_t *ctx, const vertex_t *vertex)
{
	const vertex_t *pos = NULL, *parent = NULL, *tmp = NULL;
	size_t i, j;

	if (ctx->pq_size == ctx->graph->nb_vertices)
		return (NULL);

	i = ctx->pq_size++;
	ctx->pq[i] = vertex;

	while (i > 0)
	{
		j = HEAP_PARENT(i);
		pos = ctx->pq[i];
		parent = ctx->pq[j];

		if (DISTANCE(ctx, parent) <= DISTANCE(ctx, pos))
			break;

		tmp = ctx->pq[i];
		ctx->pq[i] = ctx->pq[j];
		ctx->pq[j] = tmp;

		i = j;
	}

	IN_QUEUE(ctx, vertex) = 1;
	return (vertex);
}

/**
 * pq_extract - Extracts vertex from priority queue
 *
 * @ctx: Pointer to Dijkstra's algorithm context structure
 *
 * Return: Pointer to extracted vertex, NULL on failure
 */
static const vertex_t *pq_extract(dijkstra_ctx_t *ctx)
{
	const vertex_t *root = NULL, *tmp1 = NULL, *tmp2 = NULL;
	size_t i, j;

	if (!ctx->pq_size)
		return (NULL);

	root = ctx->pq[0];
	ctx->pq[0] = ctx->pq[--ctx->pq_size];

	for (i = 0; HEAP_LEFT(i) < ctx->pq_size; i = j)
	{
		if (HEAP_RIGHT(i) < ctx->pq_size)
		{
			tmp1 = ctx->pq[HEAP_LEFT(i)];
			tmp2 = ctx->pq[HEAP_RIGHT(i)];
			j = (DISTANCE(ctx, tmp1) <= DISTANCE(ctx, tmp2))
				? HEAP_LEFT(i)
				: HEAP_RIGHT(i);
		}
		else
		{
			j = HEAP_LEFT(i);
		}

		tmp1 = ctx->pq[i];
		tmp2 = ctx->pq[j];

		if (DISTANCE(ctx, tmp1) <= DISTANCE(ctx, tmp2))
			break;

		tmp1 = ctx->pq[i];
		ctx->pq[i] = ctx->pq[j];
		ctx->pq[j] = tmp1;
	}

	IN_QUEUE(ctx, root) = 0;
	return (root);
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
	alloc_size += graph->nb_vertices * sizeof(dijkstra_entry_t);
	alloc_size += graph->nb_vertices * sizeof(const vertex_t *);
	ctx = calloc(1, alloc_size);

	if (!ctx)
	{
		queue_delete(path);
		return (NULL);
	}

	ctx->graph = graph;
	ctx->entries = (dijkstra_entry_t *)(ctx + 1);

	for (i = 0; i < graph->nb_vertices; ++i)
		ctx->entries[i].distance = INFINITY;

	ctx->entries[start->index].distance = 0L;
	ctx->pq = (const vertex_t **)(ctx->entries + graph->nb_vertices);
	ctx->start = start;
	ctx->target = target;
	ctx->path = path;
	return (ctx);
}
