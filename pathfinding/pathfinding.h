#ifndef SYSTEMALGORITHMS_PATHFINDING_H
#define SYSTEMALGORITHMS_PATHFINDING_H

#include "graphs.h"
#include "queues.h"

/**
 * struct point_s - Structure storing coordinates
 *
 * @x: X coordinate
 * @y: Y coordinate
 */
typedef struct point_s
{
	int x, y;
} point_t;

/**
 * struct array_backtrack_ctx_s - Backtracking context
 *
 * @map: Maze grid
 * @visited: Array to track visitation
 * @rows: Number of rows
 * @cols: Number of columns
 * @target: Target point
 * @path: Queue representing the path
 */
typedef struct array_backtrack_ctx_s
{
	char **map;
	unsigned char *visited;
	int rows, cols;
	const point_t *target;
	queue_t *path;
} array_backtrack_ctx_t;

/**
 * struct graph_backtrack_ctx_s - Graph backtracking context data
 *
 * @graph: Pointer to graph_t structure
 * @visited: Array to track visitation
 * @target: Target vertex
 * @path: Queue representing the path
 */
typedef struct graph_backtrack_ctx_s
{
	graph_t *graph;
	unsigned char *visited;
	const vertex_t *target;
	queue_t *path;
} graph_backtrack_ctx_t;

/**
 * struct distance_s - Vertex min distance from start and previous vertex
 *
 * @val: Minimum distance value
 * @prev: Pointer to previous vertex in shortest path
 */
typedef struct distance_s
{
	long val;
	const vertex_t *prev;
} distance_t;

/**
 * struct dijkstra_ctx_s - Dijkstra's-algorithm context data
 *
 * @graph: Pointer to graph data structure
 * @distances: Array to track distances
 * @visited: Array to track visitation
 * @start: Pointer to start vertex
 * @target: Pointer to target vertex
 * @path: Queue representing the path
 */
typedef struct dijkstra_ctx_s
{
	graph_t *graph;
	distance_t *distances;
	unsigned char *visited;
	const vertex_t *start, *target;
	queue_t *path;
} dijkstra_ctx_t;

/* TASK 0 */
queue_t *backtracking_array(char **map, int rows, int cols,
	point_t const *start, point_t const *target);

/* TASK 1 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
	vertex_t const *target);

/* TASK 2 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
	vertex_t const *target);

#endif /* SYSTEMALGORITHMS_PATHFINDING_H */
