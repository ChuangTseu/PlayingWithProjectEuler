#include "config.h"

#if SHOWN_PROBLEM <= 20

#include <assert.h>
#include <fmt/format.h>

#include "numbers.h"
#include "bigi.h"

auto problem20_result() {
	mpz_class bigi;

	mpz_ui_pow_ui(bigi.get_mpz_t(), 2, 1000);

	mpz_fac_ui(bigi.get_mpz_t(), 100);

	std::string str_bigi = bigi.get_str();

	u64 digits_sum = 0;
	for (char c : str_bigi) {
		u64 digit_val = c - '0';

		assert(numeric_type_helper<u64>::full - digits_sum > digit_val); // Overflow detection

		digits_sum += digit_val;
	}

	return digits_sum;
	//return "NOT_IMPLEMENTED";
}

void problem20() {
	fmt::print("DO NOT CLOSE THIS CONSOLE WINDOW ACCIDENTALLY!\n\n");
	fmt::print("Solving problem 20...\n\n");

	auto res = problem20_result();

	fmt::print("The result is:\n{}\n\n", res);
}

#endif
