#include "config.h"

#include <assert.h>

#include <fmt/format.h>

#include "numbers.h"
#include "bigi.h"
#include "memoize.h"

mpz_class pieces_comb_impl(RecMemoMapT<mpz_class, u32>& memo_map, u32 pieces_sum) {
	if (pieces_sum > 100) return mpz_class(0);
	if (pieces_sum == 100) return mpz_class(1);

	return
		fn_memo_wrap(memo_map, pieces_comb_impl, pieces_sum + 50) +
		fn_memo_wrap(memo_map, pieces_comb_impl, pieces_sum + 20) +
		fn_memo_wrap(memo_map, pieces_comb_impl, pieces_sum + 10) +
		fn_memo_wrap(memo_map, pieces_comb_impl, pieces_sum + 5) +
		fn_memo_wrap(memo_map, pieces_comb_impl, pieces_sum + 2) +
		fn_memo_wrap(memo_map, pieces_comb_impl, pieces_sum + 1);
}

mpz_class pieces_comb() {
	RecMemoMapT<mpz_class, u32> memo_map;

	return pieces_comb_impl(memo_map, 0);
}

void combine_small_coins() {
	fmt::print("DO NOT CLOSE THIS CONSOLE WINDOW ACCIDENTALLY!\n\n");
	fmt::print("Solving problem 'Combine small coins'...\n\n");

	fmt::print("The result is:\n{}\n\n", pieces_comb().get_str());
}
