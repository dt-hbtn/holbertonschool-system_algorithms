#include <stdio.h>
#include <stdlib.h>
#include "pathfinding.h"

#define OUT_OF_RANGE(ctx, x, y) (\
	(x) < 0 || (x) >= (ctx)->cols || \
	(y) < 0 || (y) >= (ctx)->cols\
)

#define VISITED(ctx, x, y) ((ctx)->visited[((y) * (ctx)->rows) + (x)])

#define IS_ACCESSIBLE(ctx, x, y) ((ctx)->map[y][x] == '0')

#define END_OF_THE_LINE(ctx, x, y) (\
	OUT_OF_RANGE(ctx, x, y) || \
	!IS_ACCESSIBLE(ctx, x, y) || \
	VISITED(ctx, x, y)\
)

#define TARGET_FOUND(ctx, x, y) (\
	((ctx)->target->x == (x)) && \
	((ctx)->target->y == (y))\
)

#define ON_PATH_TO_TARGET(ctx, x, y) (\
	backtrack_r((ctx), (x) + 1, (y)) || \
	backtrack_r((ctx), (x), (y) + 1) || \
	backtrack_r((ctx), (x) - 1, (y)) || \
	backtrack_r((ctx), (x), (y) - 1)\
)

static point_t *path_push_front(backtracking_ctx_t *ctx, int x, int y);

static backtracking_ctx_t *backtracking_ctx_create(char **map, int rows,
	int cols, const point_t *target);

static point_t *backtrack_r(backtracking_ctx_t *ctx, int x, int y);

queue_t *backtracking_array(char **map, int rows, int cols,
	point_t const *start, point_t const *target)
{
	backtracking_ctx_t *ctx = NULL;
	queue_t *path = NULL;

	if (!map || !start || !target)
		return (NULL);

	ctx = backtracking_ctx_create(map, rows, cols, target);

	if (!ctx)
		return (NULL);

	if (!backtrack_r(ctx, start->x, start->y))
	{
		queue_delete(ctx->path);
		free(ctx);
		return (NULL);
	}

	path = ctx->path;
	free(ctx);
	return (path);
}

static point_t *path_push_front(backtracking_ctx_t *ctx, int x, int y)
{
	point_t *point = NULL;

	point = calloc(1, sizeof(point_t));

	if (!point)
		return (NULL);

	point->x = x;
	point->y = y;

	if (!queue_push_front(ctx->path, point))
	{
		free(point);
		return (NULL);
	}

	return (point);
}

static backtracking_ctx_t *backtracking_ctx_create(char **map, int rows,
	int cols, const point_t *target)
{
	backtracking_ctx_t *ctx = NULL;
	queue_t *path = NULL;

	path = queue_create();

	if (!path)
		return (NULL);

	ctx = calloc(1, sizeof(backtracking_ctx_t) + (size_t)(rows * cols));

	if (!ctx)
	{
		queue_delete(path);
		return (NULL);
	}

	ctx->map = map,
	ctx->visited = (unsigned char *)(ctx + 1);
	ctx->rows = rows;
	ctx->cols = cols;
	ctx->target = target;
	ctx->path = path;
	return (ctx);
}

static point_t *backtrack_r(backtracking_ctx_t *ctx, int x, int y)
{
	if (END_OF_THE_LINE(ctx, x, y))
		return (NULL);

	printf("Checking coordinates [%d, %d]\n", x, y);

	if (TARGET_FOUND(ctx, x, y))
		return (path_push_front(ctx, x, y));

	VISITED(ctx, x, y) = 1;

	if (ON_PATH_TO_TARGET(ctx, x, y))
		return (path_push_front(ctx, x, y));

	VISITED(ctx, x, y) = 0;
	return (NULL);
}
