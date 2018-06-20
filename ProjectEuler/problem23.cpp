#include "config.h"

#if SHOWN_PROBLEM <= 23

#include <assert.h>
#include <stdio.h>
#include <fmt/format.h>

#include <vector>

#include "numbers.h"
#include "bigi.h"

#include <vector>
#include <numeric>

template <class T>
using vec = std::vector<T>;

// https://stackoverflow.com/a/101613
u32 fast_ipow_positive(u32 base, u32 exp)
{
	u32 result = 1;
	for (;;)
	{
		if (exp & 1)
			result *= base;
		exp >>= 1;
		if (!exp)
			break;
		base *= base;
	}

	return result;
}

// https://www.math.upenn.edu/~deturck/m170/wk3/lecture/sumdiv.html
u32 fast_divisors_sum(u32 n) {
	vec<u32> ps;
	prime_factors(n, ps);

	typedef std::pair<vec<u32>::const_iterator, vec<u32>::const_iterator> RangePairT;

	auto curr_it = ps.cbegin();
	const auto end_it = ps.cend();

	u32 total_div_sum = 1;

	while (curr_it != end_it)
	{
		RangePairT divisor_range = std::equal_range(curr_it, ps.cend(), *curr_it);

#define MAD_MATH_SKILLZ 1

#if MAD_MATH_SKILLZ
		size_t range_size = std::distance(divisor_range.first, divisor_range.second);

		// See formula at end of article cited above
		u32 div_total_powers_sum = (fast_ipow_positive(*curr_it, static_cast<u32>(range_size + 1)) - 1) / (*curr_it - 1);
#else
		u32 div_total_powers_sum = 1; // div^0
		u32 div_curr_power = 1; // div^0

		for (auto it = divisor_range.first; it != divisor_range.second; ++it)
		{
			div_curr_power *= *it;
			div_total_powers_sum += div_curr_power;
		}

#endif
		total_div_sum *= div_total_powers_sum;

		curr_it = divisor_range.second;
	}

	return total_div_sum - n; // This method of computing the divisors sum includes the number itself as a divisor
}

bool sumof2_exists_in_sorted_vec(const vec<u32>& v, u32 tested_sum)
{
	if (v.empty()) // Todo: remove this if in the inner loop, maybe by creating two explicit versions? One til we have an array of 2, then one without the check
	{
		return false;
	}

	size_t idx_first = 0;
	size_t idx_last = v.size() - 1;

	u32 tips_sum = v[idx_first] + v[idx_last];

	do 
	{
		// Advance the first slider until we are greater or equal (and while the indices don't cross)
		while (idx_first < idx_last && tips_sum < tested_sum)
		{
			++idx_first;

			tips_sum = v[idx_first] + v[idx_last];
		}

		// Then advance the last slider until we are lower or equal (and while the indices don't cross)
		while (idx_first < idx_last && tips_sum > tested_sum)
		{
			--idx_last;

			tips_sum = v[idx_first] + v[idx_last];
		}
	} while (tips_sum != tested_sum && idx_first < idx_last); // First pass, did we find the sum? Stop! if not, did we end our scan? Stop! else, just keep going

	return tips_sum == tested_sum;
}

auto problem23_result() {
	std::vector<u32> previous_abundants;

	previous_abundants.reserve(100);

	//previous_abundants.push_back(0);

	u64 total_sum = 1;

	for (u32 i = 2; i <= 28123; ++i)
	{
		if (!sumof2_exists_in_sorted_vec(previous_abundants, i))
		{
			total_sum += i;
		}

		if (fast_divisors_sum(i) > i) // is abundant
		{
			previous_abundants.push_back(i);
		}
	}

	return total_sum;
}


void problem23() {
	fmt::print("DO NOT CLOSE THIS CONSOLE WINDOW ACCIDENTALLY!\n\n");
	fmt::print("Solving problem 23...\n\n");

	auto res = problem23_result();

	fmt::print("The result is:\n{}\n\n", res);
}

#endif
