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
 * struct backtracking_ctx_s - Backtracking context
 *
 * @map: Maze grid
 * @visited: Array to track visitation
 * @rows: Number of rows
 * @cols: Number of columns
 * @target: Target point
 * @path: Queue representing the path
 */
typedef struct backtracking_ctx_s
{
	char **map;
	unsigned char *visited;
	int rows, cols;
	const point_t *target;
	queue_t *path;
} backtracking_ctx_t;

queue_t *backtracking_array(char **map, int rows, int cols,
	point_t const *start, point_t const *target);

#endif /* SYSTEMALGORITHMS_PATHFINDING_H */
