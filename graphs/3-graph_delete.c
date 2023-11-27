#include <stdlib.h>
#include "graphs.h"

/**
 * delete_vertices - Free single vertex structure
 *
 * @vertex_list: Head pointer to vertices linked list
 */
static void
delete_vertices(vertex_t *vertex_list);

/**
 * delete_edges - Frees entire linked list of edge structures
 *
 * @edge_list: Head pointer to edges linked list
 */
static void
delete_edges(edge_t *edge_list);

/**
 * graph_delete - Graph-structure free function
 *
 * @graph: Pointer to graph structure
 */
void
graph_delete(graph_t *graph)
{
	if (!graph)
		return;

	delete_vertices(graph->vertices);
	free(graph);
}

/**
 * delete_vertices - Free single vertex structure
 *
 * @vertex_list: Head pointer to vertices linked list
 */
static void
delete_vertices(vertex_t *vertex_list)
{
	vertex_t *tmp = NULL;

	if (!vertex_list)
		return;

	do {
		tmp = vertex_list;
		vertex_list = vertex_list->next;
		delete_edges(tmp->edges);
		free(tmp);
	} while (vertex_list);
}

/**
 * delete_edges - Frees entire linked list of edge structures
 *
 * @edge_list: Head pointer to edges linked list
 */
static void
delete_edges(edge_t *edge_list)
{
	edge_t *tmp = NULL;

	if (!edge_list)
		return;

	do {
		tmp = edge_list;
		edge_list = edge_list->next;
		free(tmp);
	} while (edge_list);
}
