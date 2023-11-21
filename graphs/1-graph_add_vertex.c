#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * vertex_create - Vertex-structure allocation function
 *
 * @key: String to copy to `content` member
 * @index: Index in graph structure's `vertices` linked list
 *
 * Return: Pointer to vertex structure or NULL if allocation fails
*/
static vertex_t
*vertex_create(const char *key, size_t index);

/**
 * graph_add_vertex - Adds new vertex to graph_t instance
 *
 * @graph: Pointer to graph structure
 * @str: Key of vertex
 *
 * Return: Pointer to created vertex structure
 */
vertex_t
*graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *pos = NULL, *new_vertex = NULL;
	size_t i;

	if (!graph || !str)
		return (NULL);

	if (!graph->vertices)
	{
		new_vertex = vertex_create(str, 0);

		if (!new_vertex)
			return (NULL);

		graph->vertices = new_vertex;
		graph->nb_vertices = 1;
		return (new_vertex);
	}

	/* Move `pos` and `i` to current tail vertex, check if key already exists */
	for (i = 0, pos = graph->vertices; pos->next; ++i, pos = pos->next)
	{
		/* Fail if `str` is an existing vertex's key */
		if (!strcmp(str, pos->content))
			return (NULL);
	}

	new_vertex = vertex_create(str, i + 1);

	if (!new_vertex)
		return (NULL);

	pos->next = new_vertex;
	++graph->nb_vertices;
	return (new_vertex);
}

/**
 * vertex_create - Vertex-structure allocation function
 *
 * @key: String to copy to `content` member
 * @index: Index in graph structure's `vertices` linked list
 *
 * Return: Pointer to vertex structure or NULL if allocation fails
*/
static vertex_t
*vertex_create(const char *key, size_t index)
{
	vertex_t *vertex = NULL;

	vertex = calloc(1, sizeof(vertex_t) + strlen(key) + 1);

	if (!vertex)
		return (NULL);

	vertex->index = index;
	vertex->content = (char *)(vertex + 1);
	strcpy(vertex->content, key);
	return (vertex);
}
