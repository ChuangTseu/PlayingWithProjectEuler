#include "config.h"

#if SHOWN_PROBLEM <= 18

#include <assert.h>

#include <algorithm>

#include <fmt/format.h>

#include "numbers.h"

const u32 mini_triangle_arr[] = {
	3,
	7, 4,
	2, 4, 6,
	8, 5, 9, 3,
};

const u32 maxi_triangle_arr[] = {
	75,
	95, 64,
	17, 47, 82,
	18, 35, 87, 10,
	20, 4, 82, 47, 65,
	19, 1, 23, 75, 3, 34,
	88, 2, 77, 73, 7, 63, 67,
	99, 65, 4, 28, 6, 16, 70, 92,
	41, 41, 26, 56, 83, 40, 80, 70, 33,
	41, 48, 72, 33, 47, 32, 37, 16, 94, 29,
	53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,
	70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,
	91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,
	63, 66, 4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,
	4, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 4, 23,
};

struct Tri {
	const u32* arr;
	const u32 lines;
};

Tri mini_tri{ mini_triangle_arr , 4u };
Tri maxi_tri{ maxi_triangle_arr , 15u };

u64 rec(const Tri& tri, u32 idx, u32 line, u64 acc) {
	if (line >= tri.lines) {
		return acc;
	}

	u64 updated_acc = acc + tri.arr[idx];

	u32 next_line = line + 1;
	u32 next_idx_left = idx + line + 1;
	u32 next_idx_right = next_idx_left + 1;

	return std::max(
		rec(tri, next_idx_left, next_line, updated_acc),
		rec(tri, next_idx_right, next_line, updated_acc));
}

auto problem18_result() {
	return rec(maxi_tri, 0, 0, 0);
}

void problem18() {
	fmt::print("DO NOT CLOSE THIS CONSOLE WINDOW ACCIDENTALLY!\n\n");
	fmt::print("Solving problem 18...\n\n");

	auto res = problem18_result();

	fmt::print("The result is:\n{}\n\n", res);
}

#endif
