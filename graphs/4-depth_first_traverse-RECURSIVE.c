#include <stdlib.h>
#include "graphs.h"

/**
 * dft_r - Recursive depth-first traversal
 *
 * @vertex: Pointer to current vertex
 * @action: Function pointer to call when touching vertex
 * @depth: Current depth of vertex
 * @visited: Pointer to first element of visitation-tracking array
 *
 * Return: Current maximum depth touched
 */
static size_t
dft_r(vertex_t *vertex, action_t action, size_t depth, char *visited);

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
	size_t max_depth;
	char *visited = NULL;

	if (!graph || !graph->vertices || !action)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(char));

	if (!visited)
		return (0);

	max_depth = dft_r(graph->vertices, action, 0, visited);
	free(visited);
	return (max_depth);
}

/**
 * dft_r - Recursive depth-first traversal
 *
 * @vertex: Pointer to current vertex
 * @action: Function pointer to call when touching vertex
 * @depth: Current depth of vertex
 * @visited: Pointer to first element of visitation-tracking array
 *
 * Return: Current maximum depth touched
 */
static size_t
dft_r(vertex_t *vertex, action_t action, size_t depth, char *visited)
{
	edge_t *edge = vertex->edges;
	size_t max_depth, tmp_max;

	action(vertex, depth);
	visited[vertex->index] = 1;
	max_depth = depth;
	/* *max_depth = depth > *max_depth ? depth : *max_depth; */

	while (edge)
	{
		if (!visited[edge->dest->index])
		{
			tmp_max = dft_r(
				edge->dest,
				action,
				depth + 1,
				visited
			);

			max_depth = tmp_max > max_depth ? tmp_max : max_depth;

		}

		edge = edge->next;
	}

	return (max_depth);
}
