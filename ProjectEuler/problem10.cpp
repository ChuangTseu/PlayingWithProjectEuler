#include "config.h"

#if SHOWN_PROBLEM <= 10

#include <stdio.h>

#include <algorithm>
#include <assert.h>

#include "numbers.h"

void problem10() {
	u64 primes_sum = 0;

	for (u64 i = 2; i < 2'000'000u; ++i) {
		if (is_prime(i)) {
			primes_sum += i;
		}
	}

	printf("%llu\n", primes_sum);
}

#endif
