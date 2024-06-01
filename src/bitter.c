#include "bitter/bitter.h"

#include <limits.h>
#include <stdlib.h>

struct bitter_array bitter_array_alloc(size_t length, int width)
{
	const lldiv_t division = lldiv(length * width, CHAR_BIT);
	const bool needs_extra_byte = !!division.rem;
	const size_t bytes = division.quot + needs_extra_byte;

	return (struct bitter_array) {
		.length = length,
		.width = width,
		.bits = malloc(bytes),
	};
}

bool bitter_array_valid(struct bitter_array array)
{
	return array.bits != NULL;
}

void bitter_array_free(struct bitter_array array)
{
	free(array.bits);
}
