#include <stdlib.h>
#include "heap.h"

/**
 * heap_create - Allocates heap structure
 *
 * @data_cmp: Function pointer for item comparison
 *
 * Return: Pointer to allocated heap structure
 */
heap_t *heap_create(data_cmp_t data_cmp)
{
	heap_t *heap = NULL;

	if (!data_cmp)
		return (NULL);

	heap = calloc(1, sizeof(heap_t));

	if (!heap)
		return (NULL);

	heap->data_cmp = data_cmp;
	return (heap);
}
