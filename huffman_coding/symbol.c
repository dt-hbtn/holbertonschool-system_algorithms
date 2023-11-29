#include <stdlib.h>
#include "huffman.h"

/**
 * symbol_create - Constructs new symbol_t structure
 *
 * @data: Plaintext character
 * @freq: Frequency of plaintext character
 *
 * Return: Pointer to new symbol_t structure, NULL on failure
*/
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol = NULL;

	if (!data)
		return (NULL);

	symbol = calloc(1, sizeof(symbol_t));

	if (!symbol)
		return (NULL);

	symbol->data = data;
	symbol->freq = freq;
	return (symbol);
}
