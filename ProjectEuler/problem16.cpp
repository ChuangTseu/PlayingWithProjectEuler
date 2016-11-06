#include "config.h"

#if SHOWN_PROBLEM <= 16

#include <assert.h>

#include <algorithm>
#include <numeric>

#include <fmt/format.h>

#include "numbers.h"
#include "funct.h"

#include "bigi.h"

using result_t = u64;

char charToDigit(char c) {
	return c - '0';
}

result_t problem16_result() {
	mpz_class bigi;

	mpz_ui_pow_ui(bigi.get_mpz_t(), 2, 1000);

	std::string str_bigi = bigi.get_str();

	u64 digits_sum = 0;
	for (char c : str_bigi) {
		digits_sum += c - '0';
	}

	// Playing with accumulate
	digits_sum = std::accumulate(str_bigi.cbegin(), str_bigi.cend(), 0ull, [](u64 acc, char c) { return acc + c - '0'; });

	digits_sum = fn_sum<u64>(str_bigi.cbegin(), str_bigi.cend(), charToDigit);

	digits_sum = fn_seq_sum<u64>(str_bigi, charToDigit);

	return digits_sum;
}

void problem16() {
	fmt::print("DO NOT CLOSE THIS CONSOLE WINDOW ACCIDENTALLY!\n\n");
	fmt::print("Solving problem 16...\n\n");

	result_t res = problem16_result();

	fmt::print("The result is:\n{}\n\n", res);
}

#endif
