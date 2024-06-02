#include "bitter/bitter.h"

#include <limits.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

static lldiv_t to_bytes(size_t number_bits)
{
	return lldiv(number_bits, CHAR_BIT);
}

struct bitter_array bitter_array_alloc(size_t length, int width)
{
	const lldiv_t division = to_bytes(length * width);
	const size_t bytes = division.quot + 1;

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

int bitter_array_get(struct bitter_array array, size_t index)
{
	/*
	 * This nonsense-function has to deal with the following
	 * three conditions:
	 * - The whole number is smaller than a byte and is in
	 *   the current byte
	 * - The whole number is smaller than a byte, but overlaps
	 *   into the next byte
	 * - The whole number is larger than a byte, potentially
	 *   up to a whole word size
	 *
	 * We have to start by finding how many bits into the byte
	 * the number starts from.
	 *
	 * We potentially have to shift the value to the right, if
	 * the number ends before the end of the byte.
	 *
	 * We have to mask out the bits we're not interested in.
	 *
	 * Then, in the case that there are still bits to read, we
	 * have to move on to the next byte.
	 *
	 * And we potentially have to do this for as many bytes
	 * as can fit in a single int.
	 *
	 * I did not expect this to be this difficult when I started.
	 *
	 * I also can't figure out how to write this so it's...
	 * less confusing. And I'm sorry.
	 */
	const lldiv_t byte_index = to_bytes(index * array.width);
	const bitter *location = &array.bits[byte_index.quot];

	int result = 0;
	int start_from = byte_index.rem;

	for (int bits_remaining = array.width; bits_remaining > 0; location++) {
		const bitter
			ones = ~0,
			right_bits_ignore = MAX(0, CHAR_BIT - start_from - bits_remaining),
			mask_right = ones >> start_from,
			mask_left = ones << right_bits_ignore,
			mask = mask_left & mask_right,
			bits_read = CHAR_BIT - start_from - right_bits_ignore,
			value_here = (*location & mask) >> right_bits_ignore;

		result = (result << bits_read) + value_here;

		bits_remaining -= bits_read;
		start_from = 0;
	}

	return result;
}

void bitter_array_set(struct bitter_array array, size_t index, int value)
{
	const lldiv_t byte_index = to_bytes(index * array.width);
	bitter *location = &array.bits[byte_index.quot];

	int start_from = byte_index.rem;

	for (int bits_remaining = array.width; bits_remaining > 0; location++) {
		const bitter
			ones = ~0,
			right_bits_ignore = MAX(0, CHAR_BIT - start_from - bits_remaining),
			mask_right = ones >> start_from,
			mask_left = ones << right_bits_ignore,
			mask = ~(mask_left & mask_right),
			bits_write = CHAR_BIT - start_from - right_bits_ignore;

		*location = (*location & mask)
			+ (value >> (bits_remaining - bits_write) << right_bits_ignore);

		bits_remaining -= bits_write;
		start_from = 0;
	}
}
