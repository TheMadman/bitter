/*
 * Bitter - A library for handling arrays of arbitrary bit-length numbers
 * Copyright (C) 2024   Marcus Harrison
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BITTER_BITTER_H
#define BITTER_BITTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

/**
 * \file
 */

/**
 * \brief Type definition for bitter array elements.
 */
typedef unsigned char bitter;

/**
 * \brief A structure representing a bitter array.
 *
 * These are owning structures: they must be freed by
 * passing them to bitter_array_free() when no longer needed.
 */
struct bitter_array {
	/**
	 * \brief The number of elements currently in the
	 * 	array.
	 */
	size_t length;

	/**
	 * \brief The bit width of each element.
	 */
	int width;

	/**
	 * \brief The buffer containing the data.
	 */
	bitter *bits;
};

/**
 * \brief Allocates a new bitter_array, using the given
 * 	length and width.
 *
 * \param length The number of elements to store in the
 * 	array.
 * \param width The amount of bits for each element.
 * \returns An initialized array on success, or an array
 * 	failing bitter_array_valid() on failure.
 */
struct bitter_array bitter_array_alloc(size_t length, int width);

/**
 * \brief Tests if a given array is valid.
 *
 * \param array The array to test.
 * \returns True if the array is valid, false otherwise.
 */
bool bitter_array_valid(struct bitter_array array);

/**
 * \brief Frees the given array.
 *
 * \param array The array to free.
 */
void bitter_array_free(struct bitter_array array);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // BITTER_BITTER_H
