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
breadth_first_traverse(const graph_t *graph,
	void (*action)(const vertex_t *v, size_t depth))
{
	return (0UL);
}
