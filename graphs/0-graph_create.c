#include <stdlib.h>
#include "graphs.h"

/**
 * graph_create - Graph-structure allocation function
 *
 * Return: Pointer to graph structure or NULL if allocation fails
 */
graph_t
*graph_create(void)
{
	graph_t *graph = NULL;

	graph = calloc(1, sizeof(graph_t));

	/* No initializations needed so no NULL check needed here */
	return (graph);
}
