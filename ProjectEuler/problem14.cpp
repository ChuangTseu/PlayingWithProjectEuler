#include "config.h"

#if SHOWN_PROBLEM <= 14

#include <assert.h>

#include <algorithm>

#include "numbers.h"

#include <fmt/format.h>

using result_t = u64;

u64 chain_length(u64 number) {
	u64 count = 1;

	while (number != 1) {
		//fmt::print("{} -> ", number);
		++count;

		if ((number & 1) == 0) {
			number >>= 1;
		}
		else {
			number = 3 * number + 1;
		}
	}

	return count;
}

result_t problem14_result() {
	u64 max_length = 0;
	u64 max_number = 0;

	for (u64 i = 2; i < 1'000'000ull; ++i) {
		u64 current_length = chain_length(i);

		if (current_length > max_length) {
			max_length = current_length;
			max_number = i;
		}
	}

	return max_number;
}

void problem14() {
	fmt::print("DO NOT CLOSE THIS CONSOLE WINDOW ACCIDENTALLY!\n\n");
	fmt::print("Solving problem 14...\n\n");

	result_t res = problem14_result();

	fmt::print("The result is:\n{}\n\n", res);
}

#endif
