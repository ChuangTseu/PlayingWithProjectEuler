#include "config.h"

#if SHOWN_PROBLEM <= 4

#include <stdio.h>

#include <algorithm>

#include "numbers.h"

template <class T>
bool is_palindrom_seq(const T* first, const T* last) {
	while (first < last) {
		if (*first++ != *last--) {
			return false;
		}
	}
	return true;
}

template <int N>
bool is_palindrome_n_digits(u32 number) {
	static u32 digits[N];

	digits[0] = number % 10;
	for (u32 i = 1; i < N; ++i) {
		number /= 10;
		digits[i] = number % 10;
	}

	u32* p_first = digits;
	u32* p_last = digits + N - 1;

	return is_palindrom_seq(p_first, p_last);
}

// number must have 5 or 6 digits, otherwise behavior is undefined
bool is_palindrome_5_to_6_digits(u32 number) {
	if (number >= 100000) {
		return is_palindrome_n_digits<6>(number);
	}
	else {
		return is_palindrome_n_digits<5>(number);
	}
}

void print_is_palindrome_5_to_6_digits(u32 number) {
	printf("%u: %s\n", number, is_palindrome_5_to_6_digits(number) ? "true" : "false");
}

void problem4()
{
	u32 current_max = 0;

	for (u32 i = 999; i > 99; --i) {
		for (u32 j = i; j > 99; --j) {
			u32 product = i * j;

			if (product < current_max) {
				break;
			}

			if (is_palindrome_5_to_6_digits(product)) {
				current_max = std::max(current_max, product);
				break;
			}
		}
	}

	printf("current_max: %u\n", current_max);
}

#endif
