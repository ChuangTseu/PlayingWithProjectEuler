#include "config.h"

#if SHOWN_PROBLEM <= 7

#include <stdio.h>

#include <algorithm>

#include <assert.h>

#include "numbers.h"

void problem7() {

	u32 primes_encountered = 0;

	u64 nth_prime = 0;

	for (u64 n = 2; n < std::numeric_limits<u64>::max(); ++n) {
		if (is_prime(n)) {
			++primes_encountered;

			if (primes_encountered == 10'001u) {
				nth_prime = n;
				break;
			}
		}
	}

	printf("nth_prime: %llu\n", nth_prime);
}

#endif
