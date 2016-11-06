#include "config.h"

#if SHOWN_PROBLEM <= 15

#include <assert.h>

#include <algorithm>

#include <fmt/format.h>

#include "numbers.h"
#include "arrays.h"
#include "bigi.h"
#include "memoize.h"

u64 rec_memo_impl(RecMemoMapT<u64, u32, u32, u32>& memo_map, u32 n, u32 i, u32 j) {
	if (i > n || j > n) return 0;

	if (i == n && j == n) return 1;

	return
		fn_memo_wrap(memo_map, rec_memo_impl, n, i + 1, j) +
		fn_memo_wrap(memo_map, rec_memo_impl, n, i, j + 1);
}

u64 rec_memo(u32 n) {
	RecMemoMapT<u64, u32, u32, u32> memo_map;

	return rec_memo_impl(memo_map, n, 0, 0);
}

u32 N = 20;

// Memoizing make it go faster than light !
// But you'd better go for the combinatorial formula anyway :)
u64 naive_memoize_array[40][40];

u64 naive_rec(u32 i, u32 j) {
	u64 memoized_value = naive_memoize_array[i][j];

	if (memoized_value != npos<u64>::value) {
		return memoized_value;
	}

	if (i > N || j > N) {
		return 0;
	}

	if (i == N && j == N) {
		return 1;
	}

	u64 res = naive_rec(i + 1, j) + naive_rec(i, j + 1);
	naive_memoize_array[i][j] = res;

	return res;
}

using result_t = u64;

std::string digit_to_str(int digit) {
	return std::string(10, static_cast<char>(digit) + '0');
}

result_t problem15_result() {
	result_t res = 0;

	for (N = 1; N <= 20; ++N) {
		for (size_t i = 0; i < ARRAY_FULL_EXTENT(naive_memoize_array); ++i) {
			((u64*)naive_memoize_array)[i] = npos<u64>::value;
		}

		fmt::print("{} vs {}\n", naive_rec(0, 0), rec_memo(N));
	}

	return 0;
}

constexpr u64 BOBN = 20;

u64 compute_NN() {
	u64 l[BOBN][BOBN];

	std::fill_n((u64*)l, BOBN * BOBN, 0ull);

	u64 l0 = BOBN + 1;

	//l1[0] = l0 - 1;
	//l1[1] = l0 - 2;
	//l1[2] = l0 - 3;
	//l1[3] = l0 - 4;
	for (u32 j = 0; j < BOBN; ++j) {
		l[1][j] = l0 - j - 1;
	}

	//l2[0] = l1[0 ++ + last];
	//l2[1] = l1[1 ++ + last];
	//l2[2] = l1[2 ++ + last];
	//l2[3] = l1[3 ++ + last];
	// ...
	for (u32 i = 2; i < BOBN; ++i) {
		for (u32 j = 0; j < BOBN; ++j) {
			for (u32 k = j; k < BOBN; ++k) {
				l[i][j] += l[i - 1][k];
			}
		}
	}

	u64 sum = l0;
	for (u32 i = 0; i < BOBN * BOBN; ++i) {
		sum += ((u64*)l)[i];
	}

	return sum;
}


#include "bigi.h"

int arr_0[3];
constexpr size_t extof_0 = full_extent<decltype(arr_0)>::value;
constexpr size_t extof_1 = full_extent<int[5][5][4]>::value;

void problem15() {
	fmt::print("DO NOT CLOSE THIS CONSOLE WINDOW ACCIDENTALLY!\n\n");
	fmt::print("Solving problem 15...\n\n");

	fmt::print("extof_0: {}\n", extof_0);
	fmt::print("extof_1: {}\n", extof_1);

	//std::fill_n(std::underl)

	u64 res = problem15_result();
	//u64 res = compute_NN();

	// Via the https://en.wikipedia.org/wiki/Central_binomial_coefficient method

	// Cf http://mathschallenge.net/full/random_routes

	/*
	Could be also thought as:

	Given N == 20,
	a correct path length will always be 40.

	How many ways are there to obtain 20 RIGHT moves (or 20 DOWN moves) from among 40 total moves ?

	Binomial coefficient gives us : 
		40! / ((40 - 20)! * (20)!)
		40! / (20!*20!)

	Generalized for n:
		2n! / (n!*n!)
	*/

	// factorial(40) goes way beyond the u64 limits
	mpz_class bigfac_40;
	mpz_fac_ui(bigfac_40.get_mpz_t(), 40);

	mpz_class bigfac_20;
	mpz_fac_ui(bigfac_20.get_mpz_t(), 20);

	mpz_class central_binomial = bigfac_40 / (bigfac_20 * bigfac_20);

	//std::string res = central_binomial.get_str();

	fmt::print("The result is:\n{}\n\n", res);
}

#endif
