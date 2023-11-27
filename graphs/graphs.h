#ifndef SYSTEMALGORITHMS_GRAPHS_H
#define SYSTEMALGORITHMS_GRAPHS_H

#include <stddef.h>

/**
 * enum edge_type_e - Enumerates the different types of
 * connection between two vertices
 *
 * @UNIDIRECTIONAL: The connection is made only in one way
 * @BIDIRECTIONAL: The connection is made in two ways
 */
typedef enum edge_type_e
{
	UNIDIRECTIONAL = 0,
	BIDIRECTIONAL
} edge_type_t;

/* Define the structure temporarily for usage in the edge_t */
typedef struct vertex_s vertex_t;

/**
 * struct edge_s - Node in the linked list of edges for a given vertex
 * A single vertex can have many edges
 *
 * @dest: Pointer to the connected vertex
 * @next: Pointer to the next edge
 */
typedef struct edge_s
{
	vertex_t *dest;
	struct edge_s *next;
} edge_t;

/**
 * struct vertex_s - Node in the linked list of vertices in the adjacency list
 *
 * @index: Index of the vertex in the adjacency list.
 * @content: Custom data stored in the vertex (here, a string)
 * @nb_edges: Number of conenctions with other vertices in the graph
 * @edges: Pointer to the head node of the linked list of edges
 * @next: Pointer to the next vertex in the adjacency linked list
 *   This pointer points to another vertex in the graph, but it
 *   doesn't stand for an edge between the two vertices
 */
struct vertex_s
{
	size_t index;
	char *content;
	size_t nb_edges;
	edge_t *edges;
	struct vertex_s *next;
};

/**
 * struct graph_s - Representation of a graph
 * We use an adjacency linked list to represent our graph
 *
 * @nb_vertices: Number of vertices in our graph
 * @vertices: Pointer to the head node of our adjacency linked list
 */
typedef struct graph_s
{
	size_t nb_vertices;
	vertex_t *vertices;
} graph_t;

typedef void (*action_t)(const vertex_t *v, size_t depth);

/**
 * vertex_tracker_s - Composite struct for tracking visited vertices
 *
 * @vertex: Pointer to vertex structure
 * @depth: Depth of vertex
 */
typedef struct vertex_tracker_s
{
	vertex_t *v;
	size_t d;
} vertex_tracker_t;

/**
 * graph_create - Graph-structure allocation function
 *
 * Return: Pointer to graph structure or NULL if allocation fails
 */
graph_t
*graph_create(void);


/**
 * graph_add_vertex - Adds new vertex to graph_t instance
 *
 * @graph: Pointer to graph structure
 * @str: Key of vertex
 *
 * Return: Pointer to created vertex structure
 */
vertex_t
*graph_add_vertex(graph_t *graph, const char *str);

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
	edge_type_t type);


/**
 * graph_delete - Graph-structure free function
 *
 * @graph: Pointer to graph structure
 */
void
graph_delete(graph_t *graph);

/**
 * depth_first_traverse - Acts on all graph vertices (depth-first order)
 *
 * @graph: Pointer to graph structure
 * @action: Function pointer that will be called for all vertices
 *
 * Return: The greatest vertex depth or 0UL on failure
 */
size_t
depth_first_traverse(const graph_t *graph, action_t action);

/**
 * breadth_first_traverse - Acts on all graph vertices (breadth-first order)
 *
 * @graph: Pointer to graph structure
 * @action: Function pointer that will be called for all vertices
 *
 * Return: The greatest vertex depth or 0UL on failure
 */
size_t
breadth_first_traverse(const graph_t *graph, action_t action);

/**
 * graph_display - Utility function to display the adjacency linked list
 *
 * @graph: Pointer to the graph structure to be displayed
 */
void
graph_display(const graph_t *graph);

#endif /* SYSTEMALGORITHMS_GRAPHS_H */
