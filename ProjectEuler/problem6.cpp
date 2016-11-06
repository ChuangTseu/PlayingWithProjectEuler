#include "config.h"

#if SHOWN_PROBLEM <= 6

#include <stdio.h>

#include <algorithm>

#include "numbers.h"

void problem6() {

	i32 square_sum = 0;
	i32 sum = 0;

	for (i32 n = 1; n < 101; ++n) {
		square_sum += n * n;
		sum += n;
	}

	i32 sum_squared = sum * sum;

	i32 diff = sum_squared - square_sum;

	printf("diff: %d\n", diff);
}

#endif
