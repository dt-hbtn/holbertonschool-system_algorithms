#include <stdlib.h>
#include "huffman.h"

symbol_t
*symbol_create(char data, size_t freq)
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
