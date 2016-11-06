#include "config.h"

#if SHOWN_PROBLEM <= 5

#include <stdio.h>

#include <algorithm>

#include "numbers.h"

void problem5() {
	u32 smalest_n = 0;

	for (u32 n = 20;; n += 20) {
		if (is_divisible_by(n, 20u) &&
			is_divisible_by(n, 19u) && 
			is_divisible_by(n, 18u) && 
			is_divisible_by(n, 17u) && 
			is_divisible_by(n, 16u) && 
			is_divisible_by(n, 15u) && 
			is_divisible_by(n, 14u) && 
			is_divisible_by(n, 13u) && 
			is_divisible_by(n, 12u) && 
			is_divisible_by(n, 11u)) {
			smalest_n = n;
			break;
		}
	}

	printf("smalest_n: %u\n", smalest_n);
}

#endif
