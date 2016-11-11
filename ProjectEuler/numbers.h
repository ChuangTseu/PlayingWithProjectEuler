#pragma once

#include <stdint.h>
#include <vector>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

template <class UNSIGNED_T>
struct npos {
	static constexpr UNSIGNED_T value = ~static_cast<UNSIGNED_T>(0);
};

template <class NUMBER_T>
struct numeric_type_helper {
	static constexpr size_t bitcount = sizeof(NUMBER_T) * 8; // could use std::numeric_limits<NUMBER_T>::digits

	static constexpr NUMBER_T msb = static_cast<NUMBER_T>(1) << (bitcount - 1);
	static constexpr NUMBER_T lsb = static_cast<NUMBER_T>(1);

	static constexpr NUMBER_T from_msb(size_t rshift) {
		return static_cast<NUMBER_T>(1) << (bitcount - 1 - rshift);
	}

	static constexpr NUMBER_T from_lsb(size_t lshift) {
		return static_cast<NUMBER_T>(1) << (lshift);
	}

	static constexpr NUMBER_T full = ~static_cast<NUMBER_T>(0);
};

constexpr u32 ieee754_float_last_precise_integer = static_cast<u32>(1) << 24;
constexpr u64 ieee754_double_last_precise_integer = static_cast<u64>(1) << 53;

// https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Binary_numeral_system_.28base_2.29
template <class POSITIVE_T>
POSITIVE_T integer_sqrt(POSITIVE_T unumber)
{
	POSITIVE_T op = unumber;
	POSITIVE_T res = 0;
	POSITIVE_T one = numeric_type_helper<POSITIVE_T>::from_msb(1);

	while (one > op) {
		one >>= 2;
	}

	while (one != 0) {
		if (op >= res + one) {
			op = op - (res + one);
			res = res + 2 * one;
		}
		res >>= 1;
		one >>= 2;
	}
	return res;
}

template <class NUMBER_T>
bool is_divisible_by(NUMBER_T number, NUMBER_T factor) {
	return (number % factor) == 0;
}

template <class NUMBER_T>
bool is_prime(NUMBER_T number) {
	if (number < 2) {
		return false;
	}

	NUMBER_T square_root = integer_sqrt(number);

	for (NUMBER_T factor = 2; factor <= square_root; ++factor) {
		if (is_divisible_by(number, factor)) {
			return false;
		}
	}

	return true;
}

template <class NUMBER_T>
void prime_factors(NUMBER_T number, std::vector<NUMBER_T>& factors) {
	NUMBER_T sentinel_n = integer_sqrt(number) + 1;
	for (NUMBER_T i = 2; i < sentinel_n; ++i) {
		if (is_divisible_by(number, i)) {
			factors.push_back(i);
			prime_factors(number / i, factors);
			return;
		}
	}

	factors.push_back(number);
}

// Do not use with 0 or 1
template <class NUMBER_T>
NUMBER_T opt_divisor_count(NUMBER_T number, std::vector<NUMBER_T>& reused_optimization_buffer) {
	std::vector<NUMBER_T>& factors = reused_optimization_buffer;

	factors.clear();
	prime_factors(number, factors);

	// factors is guarenteed to have at least one element, starting the check on the second element (if any)
	u32 idx = 1;
	for (; idx < factors.size() && factors[idx] == factors[0]; ++idx);

	// http://stackoverflow.com/questions/110344/algorithm-to-calculate-the-number-of-divisors-of-a-given-number#comment22161_110564
	NUMBER_T divisors_count = 1 + idx;

	while (idx < factors.size()) {
		u32 last_idx = idx++;
		for (; idx < factors.size() && factors[idx] == factors[last_idx]; ++idx);

		divisors_count *= (1 + (idx - last_idx));
	}

	return divisors_count;
}

