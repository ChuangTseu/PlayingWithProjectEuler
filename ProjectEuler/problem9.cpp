#include "config.h"

#if SHOWN_PROBLEM <= 9

#include <stdio.h>

#include <algorithm>
#include <assert.h>

#include "numbers.h"

void problem9() {
	u32 abc = 0;

	for (u32 a = 1; a <= 332; ++a) {
		for (u32 b = a + 1; b <= 1000 - a - 1; ++b) {
			u32 c = 1000 - a - b;
			if (a * a + b * b == c * c) {
				printf("a: %u, b: %u, c: %u\n", a, b, c);
				abc = a * b * c;
				goto result_found;
			}
		}
	}

result_found:
	printf("%u\n", abc);
}

#endif
