#ifndef SYSTEMALGORITHMS_HUFFMANCODING_HUFFMAN_H
#define SYSTEMALGORITHMS_HUFFMANCODING_HUFFMAN_H

#include <stddef.h>

/**
 * struct symbol_s - Stores a char and its associated frequency
 *
 * @data: The character
 * @freq: The associated frequency
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;

#endif /* SYSTEMALGORITHMS_HUFFMANCODING_HUFFMAN_H */