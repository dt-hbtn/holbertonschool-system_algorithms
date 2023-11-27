#include <stdlib.h>
#include "graphs.h"

/**
 * breadth_first_traverse - Acts on all graph vertices (breadth-first order)
 *
 * @graph: Pointer to graph structure
 * @action: Function pointer that will be called for all vertices
 *
 * Return: The greatest vertex depth or 0UL on failure
 */
size_t
breadth_first_traverse(const graph_t *graph, action_t action)
{
	size_t max_depth = 0;
	vertex_tracker_t *queue = NULL, *pos = NULL;
	edge_t *edge = NULL;
	unsigned char *visited = NULL;
	long qfront = 0, qback = 0;

	if (!graph || !graph->vertices || !action)
		return (0);

	queue = calloc(graph->nb_vertices, sizeof(vertex_tracker_t));

	if (!queue)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(unsigned char));

	if (!visited)
	{
		free(queue);
		return (0);
	}

	queue->v = graph->vertices;
	visited[0] = 1;

	while (qfront <= qback)
	{
		pos = queue + qfront++;
		action(pos->v, pos->d);

		for (edge = pos->v->edges; edge; edge = edge->next)
		{
			if (!visited[edge->dest->index])
			{
				++qback;
				queue[qback].v = edge->dest;
				queue[qback].d = pos->d + 1;
				visited[edge->dest->index] = 1;

				if (queue[qback].d > max_depth)
					max_depth = queue[qback].d;
			}
		}
	}

	free(queue);
	free(visited);
	return (max_depth);
}
