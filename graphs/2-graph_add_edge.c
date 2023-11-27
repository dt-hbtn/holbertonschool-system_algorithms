#include <stdlib.h>
#include <string.h>
#include "graphs.h"

#define EDGE_TYPE_VALID(et) ((et) >= UNIDIRECTIONAL && (et) <= BIDIRECTIONAL)

/**
 * search_vertices - Find src/dest vertices by key
 *
 * @ctx: Pointer to search-context structure
 *
 * Return: Non-0 if both src/dest vertices found, otherwise 0
 */
static int
search_vertices(vertex_search_ctx_t *ctx);

/**
 * vertex_add_edge - Adds a new edge to a vertex
 *
 * @vertex: Pointer to source vertex to which an edge will be added
 * @dest: Pointer to destination vertex
 *
 * Return: Pointer to new edge structure
 */
static edge_t
*vertex_add_edge(vertex_t *vertex, vertex_t *dest);

/**
 * graph_add_edge - Adds an edge between two vertices
 *
 * @graph: Pointer to graph structure
 * @src: Key of source vertex
 * @dest: Key of destination vertex
 * @type: Edge type (UNIDIRECTIONAL or BIDIRECTIONAL)
 *
 * Return: 1 on success, 0 on failure
 */
int
graph_add_edge(graph_t *graph, const char *src, const char *dest,
	edge_type_t type)
{
	vertex_search_ctx_t search_ctx = { src, dest, NULL, NULL, NULL };

	if (!graph || !src || !dest || !EDGE_TYPE_VALID(type))
		return (0);

	search_ctx.vertex_list = graph->vertices;

	if (!search_vertices(&search_ctx))
		return (0);

	if (!vertex_add_edge(search_ctx.src, search_ctx.dest))
		return (0);

	if (type == BIDIRECTIONAL)
	{
		if (!vertex_add_edge(search_ctx.dest, search_ctx.src))
			return (0);
	}

	return (1);
}

/**
 * search_vertices - Find src/dest vertices by key
 *
 * @ctx: Pointer to search-context structure
 *
 * Return: 1 if both src/dest vertices found, 0 if not
 */
static int
search_vertices(vertex_search_ctx_t *ctx)
{
	vertex_t *pos = ctx->vertex_list;

	if (!pos)
		return (0);

	do {
		if (!ctx->src && !strcmp(pos->content, ctx->src_key))
			ctx->src = pos;

		if (!ctx->dest && !strcmp(pos->content, ctx->dest_key))
			ctx->dest = pos;

		pos = pos->next;
	} while (pos && (!ctx->src || !ctx->dest));

	return (ctx->src && ctx->dest);
}


/**
 * vertex_add_edge - Adds a new edge to a vertex
 *
 * @vertex: Pointer to source vertex to which an edge will be added
 * @dest: Pointer to destination vertex
 *
 * Return: Pointer to new edge structure
 */
static edge_t
*vertex_add_edge(vertex_t *vertex, vertex_t *dest)
{
	edge_t *edge = NULL, *pos = NULL;

	edge = calloc(1, sizeof(edge_t));

	if (!edge)
		return (NULL);

	edge->dest = dest;

	if (!vertex->edges)
	{
		vertex->edges = edge;
		vertex->nb_edges = 1;
		return (edge);
	}

	/* Move `pos` to current tail edge, check if `dest` already exists */
	for (pos = vertex->edges; pos->next; pos = pos->next)
	{
		if (pos->dest == dest)
		{
			free(edge);
			return (NULL);
		}
	}

	pos->next = edge;
	++vertex->nb_edges;

	return (edge);
}
