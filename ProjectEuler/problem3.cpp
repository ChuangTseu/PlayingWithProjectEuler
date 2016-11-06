#include "config.h"

#if SHOWN_PROBLEM <= 3

#include <stdio.h>

#include <algorithm>

#include "numbers.h"

u64 max_prime_decomposition(u64 number) {
	for (u64 i = 2; i < number; ++i) {
		if (is_divisible_by(number, i)) {
			u64 left_factor = i;
			u64 right_factor = number / i;

#if !MAX_PRIME_DECOMPOSITION_RIGHT_LEFT
			return std::max(max_prime_decomposition(left_factor), max_prime_decomposition(right_factor));
#else 
			return std::max(max_prime_decomposition(right_factor), max_prime_decomposition(left_factor));
#endif
		}
	}

	return number;
}

/*
Problem 3
Largest prime factor

The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
*/

void print_max_prime_decomposition(u64 number) {
	printf("%llu: %llu\n", number, max_prime_decomposition(number));
}

void problem3()
{
	u64 test_n = 13195;

	print_max_prime_decomposition(4);
	print_max_prime_decomposition(5);
	print_max_prime_decomposition(6);
	print_max_prime_decomposition(7);
	print_max_prime_decomposition(8);
	print_max_prime_decomposition(13195);
	print_max_prime_decomposition(600851475143ull);

	printf("I'm problem3!\n");
}

#endif
