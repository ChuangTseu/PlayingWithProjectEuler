#include "config.h"

#if SHOWN_PROBLEM <= 12

#include <stdio.h>

#include <algorithm>
#include <assert.h>

#include "numbers.h"

u64 factorial(u64 number) {
	if (number == 0) {
		return 1;
	}

	u64 fact_product = number--;
	while (number > 1) {
		fact_product *= number--;
	}

	return fact_product;
}

u64 divisor_count(u64 number) {
	if (number == 1) {
		return 1;
	}

	u64 count = 2; // 1 and number
	u64 max_factor = number / 2;

	for (u64 factor = 2; factor <= max_factor; ++factor) {
		if (is_divisible_by(number, factor)) {
			++count;
		}
	}

	return count;
}

// See http://stackoverflow.com/questions/110344/algorithm-to-calculate-the-number-of-divisors-of-a-given-number
// And the great answer: http://stackoverflow.com/a/110365/6267305
void problem12() {

	std::vector<u64> reused_optimisation_buffer;
	reused_optimisation_buffer.reserve(100);

	u64 triangular_sum = 1;

	for (u64 i = 2; triangular_sum < npos<u64>::value - i; ++i) {
		triangular_sum += i;

		if (opt_divisor_count(triangular_sum, reused_optimisation_buffer) > 500) {
			printf("%llu\n", triangular_sum);
			return;
		}
	}

	printf("Could not find a match!\n");
	int breakpoint = -1;
}

#endif
