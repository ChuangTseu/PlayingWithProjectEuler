#include "config.h"

#if SHOWN_PROBLEM <= 21

#include <assert.h>

#include <algorithm>

#include <fmt/format.h>

#include "numbers.h"
#include "memoize.h"

#include <vector>
#include <numeric>

template <class T>
using vec = std::vector<T>;

void combined_mults(const std::vector<std::vector<u32>>& packs, u32 path_acc, std::vector<u32>& out_all_divisors) {
	if (packs.empty()) {
		out_all_divisors.push_back(path_acc);
		return;
	}

	std::vector<std::vector<u32>> rest_packs(packs.cbegin() + 1, packs.cend());

	for (u32 val : packs[0]) {
		combined_mults(rest_packs, path_acc * val, out_all_divisors);
	}
}

u32 sum_combined_mults(const std::vector<const std::vector<u32>*>& packs, u32 pack_idx, u32 path_acc) {
	if (pack_idx == packs.size()) return path_acc;

	return std::accumulate(packs[pack_idx]->cbegin(), packs[pack_idx]->cend(), 0,
		[&packs, pack_idx, path_acc](u32 acc, u32 mult) { return acc + sum_combined_mults(packs, pack_idx + 1, path_acc * mult); });
}

u32 divisors_sum_withitself(u32 n) {
	vec<u32> ps;
	prime_factors(n, ps);

	typedef std::pair<vec<u32>::const_iterator, vec<u32>::const_iterator> RangePairT;

	vec<vec<u32>> mults_comb;
	u32 mults_comb_idx = 0;

	for (size_t i = 0; i < ps.size();) {
		mults_comb.emplace_back();
		u32 acc = 1;
		mults_comb[mults_comb_idx].push_back(acc);

		auto range = std::equal_range(ps.cbegin(), ps.cend(), ps[i]);

		size_t s = std::distance(range.first, range.second);

		for (auto it = range.first; it != range.second; ++it) {
			acc *= *it;
			mults_comb[mults_comb_idx].push_back(acc);
		}

		i += s;
		++mults_comb_idx;
	}

	vec<const vec<u32>*> mults_comb_ptrs(mults_comb.size());
	std::iota(mults_comb_ptrs.begin(), mults_comb_ptrs.end(), mults_comb.data());

	return sum_combined_mults(mults_comb_ptrs, 0, 1);
}

u32 divisors_sum(u32 n) {
	return divisors_sum_withitself(n) - n;
}

bool amicables(u32 i, u32 j) {
	return (i == divisors_sum(j) && j == divisors_sum(i));
}

u32 divisors_sum_memo(u32 n) {
	static SingleArgRecMemoMapT<u32, u32> memo_map;
	return fn_memo_wrap(memo_map, divisors_sum, n);
}

bool amicables_memo(u32 i, u32 j) {
	return (i == divisors_sum_memo(j) && j == divisors_sum_memo(i));
}

u32 solve(u32 below_n) {
	u32 sum = 0;

	for (u32 i = 2; i < below_n; ++i) {
		for (u32 j = 2; j < below_n; ++j) {
			if (i == j) continue;

			if (amicables_memo(i, j)) {
				//fmt::print("{} {}\n", i, j);
				sum += i;
			}
		}
	}

	return sum;
}

auto problem21_result() {

	fmt::print("{}\n", amicables(220, 284));
	fmt::print("{}\n", amicables(220, 285));

	return solve(10000);

	u32 ds = divisors_sum(12);

	std::vector<u32> all_divisors;

	std::vector<std::vector<u32>> packs{ { 1, 2, 4 }, { 1, 5 }, { 1, 11 } };
	//std::vector<const std::vector<u32> *> packs_crefs{ packs.cbegin(), packs.cend() };

	std::vector<const std::vector<u32>*> ptrs(packs.size());
	std::iota(ptrs.begin(), ptrs.end(), packs.data());

	for (const std::vector<u32>* p : ptrs) {
		fmt::print("{}, ", (size_t)p);
	}
	fmt::print("\n");
	for (const std::vector<u32>& r : packs) {
		fmt::print("{}, ", (size_t)&r);
	}

	fmt::print("\n\n");

	fmt::print("sizeof ptrs[0]: {}\n", sizeof(ptrs[0]));
	fmt::print("sizeof const std::vector<u32>*: {}\n", sizeof(const std::vector<u32>*));

	fmt::print("diff: {}\n", (((size_t)ptrs[1]) - ((size_t)ptrs[0])));

	bool eq = (((size_t)ptrs[1]) - ((size_t)ptrs[0])) == sizeof(ptrs[0]);
	fmt::print("Eq? {}\n", eq);

	const std::vector<u32>* p0 = nullptr;
	const std::vector<u32>* p1 = p0 + 1;

	constexpr size_t sizeof_vecptr = sizeof(const std::vector<u32>*);
	constexpr size_t sizeof_vec = sizeof(std::vector<u32>);

	fmt::print("p0: {}, p1: {}\n", (size_t)p0, (size_t)p1);

	//assert((((size_t)ptrs[1]) - ((size_t)ptrs[0])) == sizeof(ptrs[0]));

	fmt::print("\n\n");

	combined_mults(packs, 1, all_divisors);

	std::sort(all_divisors.begin(), all_divisors.end());

	u32 sum2 = sum_combined_mults(ptrs, 0, 1);

	for (u32 d : all_divisors) {
		fmt::print("{}, ", d);
	}

	fmt::print("\n\n");
	fmt::print("sum2_combined_mults: {}\n", sum2);
	fmt::print("\n\n");

	//return "NOT_IMPLEMENTED";
}

void problem21() {
	fmt::print("DO NOT CLOSE THIS CONSOLE WINDOW ACCIDENTALLY!\n\n");
	fmt::print("Solving problem 21...\n\n");

	auto res = problem21_result();

	fmt::print("The result is:\n{}\n\n", res);
}

#endif
