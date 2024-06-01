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

#include "test_macros.h"
#include <bitter/bitter.h>

void test_alloc_success()
{
	struct bitter_array array = bitter_array_alloc(4, 3);
	assert(bitter_array_valid(array));

	bitter_array_free(array);
}

int main()
{
	test_alloc_success();
}
