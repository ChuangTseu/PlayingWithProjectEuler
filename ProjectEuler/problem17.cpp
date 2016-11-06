#include "config.h"

#if SHOWN_PROBLEM <= 17

#include <assert.h>

#include <algorithm>
#include <string>

#include <fmt/format.h>

#include "numbers.h"
#include "arrays.h"

using result_t = u32;

std::string lut_str_unit[] = { "", "one", "two" , "three" , "four" , "five" , "six" , "seven" , "eight" , "nine" };
u32 lut_unit_lettercount[] = { 0, 3, 3, 5, 4, 4, 3, 5, 5, 4 };

std::string lut_str_special_tenth[] = { "ten", "eleven", "twelve" , "thirteen" , "fourteen" , "fifteen" , "sixteen" , "seventeen" , "eighteen" , "nineteen" };
u32 lut_special_tenth_lettercount[] = { 3, 6, 6, 8, 8, 7, 7, 9, 8, 8 };

std::string lut_str_tenth[] = { "", "ten", "twenty" , "thirty" , "forty" , "fifty" , "sixty" , "seventy" , "eighty" , "ninety" };
u32 lut_tenth_lettercount[] = { 0, 3, 6, 6, 5, 5, 5, 7, 6, 6 };

u32 parse_1_digits(u32& number) {
	u32 digits1 = number % 10;
	number /= 10;
	return digits1;
}

u32 parse_2_digits(u32& number) {
	u32 digits2 = number % 100;
	number /= 100;
	return digits2;
}

std::string compose_full_hundredth_str(u32 hundredth_1_digit, u32 tenth_full_2_digits) {
	std::string local_buffer;

	if (hundredth_1_digit > 0) {
		local_buffer += lut_str_unit[hundredth_1_digit] + " hundred";

		if (tenth_full_2_digits > 0) {
			local_buffer += " and ";
		}
	}

	if (tenth_full_2_digits > 0) {
		if (tenth_full_2_digits < 10) {
			local_buffer += lut_str_unit[tenth_full_2_digits];
		}
		else if (tenth_full_2_digits < 20) {
			local_buffer += lut_str_special_tenth[tenth_full_2_digits - 10];
		}
		else {
			u32 tenth = tenth_full_2_digits / 10;
			u32 unit = tenth_full_2_digits % 10;
			local_buffer += lut_str_tenth[tenth];
			if (unit > 0) {
				local_buffer += "-" + lut_str_unit[unit];
			}
		}
	}

	return local_buffer;
}

std::string major_qualifiers[] = { "", "thousand", "million", "billion" };
u32 major_qualifiers_lettercount[] = { 0, 8, 7, 7 };

std::string to_english_number(u32 number) {
	std::string local_buffer;

	// if 0 then zero
	if (number == 0) {
		return "zero";
	}

	u32 current_major_qualifier_idx = 0;

	do {
		// parse_2_digits
		u32 tenth_full_2_digits = parse_2_digits(number);
		// parse_1_digits
		u32 hundredth_1_digit = parse_1_digits(number);
		// compose hundredth str with current major qualifier
		std::string full_hundredth_str_qualified;
		if (tenth_full_2_digits + hundredth_1_digit > 0) {
			full_hundredth_str_qualified = compose_full_hundredth_str(hundredth_1_digit, tenth_full_2_digits);

			if (!major_qualifiers[current_major_qualifier_idx].empty()) {
				full_hundredth_str_qualified += " " + major_qualifiers[current_major_qualifier_idx];
			}
		}

		if (!full_hundredth_str_qualified.empty()) {
			if (local_buffer.empty()) {
				local_buffer = full_hundredth_str_qualified;
			}
			else {
				local_buffer = full_hundredth_str_qualified + " " + local_buffer;
			}
		}

		++current_major_qualifier_idx;
	} while (number > 0);

	return local_buffer;
}

void validate_luts() {
	assert(ARRAY_SIZE(lut_str_unit) == ARRAY_SIZE(lut_unit_lettercount));
	for (u32 i = 0; i < ARRAY_SIZE(lut_str_unit); ++i) {
		assert(lut_str_unit[i].length() == lut_unit_lettercount[i]);
	}

	assert(ARRAY_SIZE(lut_str_tenth) == ARRAY_SIZE(lut_tenth_lettercount));
	for (u32 i = 0; i < ARRAY_SIZE(lut_str_tenth); ++i) {
		assert(lut_str_tenth[i].length() == lut_tenth_lettercount[i]);
	}

	assert(ARRAY_SIZE(lut_str_special_tenth) == ARRAY_SIZE(lut_special_tenth_lettercount));
	for (u32 i = 0; i < ARRAY_SIZE(lut_str_special_tenth); ++i) {
		assert(lut_str_special_tenth[i].length() == lut_special_tenth_lettercount[i]);
	}

	assert(ARRAY_SIZE(major_qualifiers) == ARRAY_SIZE(major_qualifiers_lettercount));
	for (u32 i = 0; i < ARRAY_SIZE(major_qualifiers); ++i) {
		assert(major_qualifiers[i].length() == major_qualifiers_lettercount[i]);
	}
}

u32 valid_letters_count(const std::string& num_str) {
	return (u32) std::count_if(num_str.cbegin(), num_str.cend(), [](char c) { return c >= 'a' && c <= 'z'; });
}

result_t problem17_result() {
	// validate_luts(); // DONE! OK!

	u32 total_letters_count = 0;

	for (u32 i = 1; i <= 1000; ++i) {
		std::string as_english_number = to_english_number(i);
		u32 letters_count = valid_letters_count(as_english_number);

		fmt::print("{:=3}: {} {}\n", i, as_english_number, letters_count);

		total_letters_count += letters_count;
	}

	return total_letters_count;
}

void problem17() {
	fmt::print("DO NOT CLOSE THIS CONSOLE WINDOW ACCIDENTALLY!\n\n");
	fmt::print("Solving problem 17...\n\n");

	result_t res = problem17_result();

	fmt::print("The result is:\n{}\n\n", res);
}

#endif
