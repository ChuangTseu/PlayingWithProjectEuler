#pragma once

template <class T>
struct full_extent {
	static constexpr size_t value = extent_upto_rank<T, std::rank<T>::value - 1>::value;
};

template <class T, signed N>
struct extent_upto_rank {
	static constexpr size_t value = std::extent<T, N>::value * extent_upto_rank<T, N - 1>::value;
};

template <class T>
struct extent_upto_rank<T, -1>;

template <class T>
struct extent_upto_rank<T, 0> {
	static constexpr size_t value = std::extent<T, 0>::value;
};

#define ARRAY_SIZE(arr) std::extent<decltype(arr)>::value

#define ARRAY_FULL_EXTENT(arr) full_extent<decltype(arr)>::value

//template <class T[], class ELEMT>
//void array_fill_all(T arr, const ELEMT& val) {
//	typedef std::remove_all_extents<T>::type ElemType;
//
//	for (size_t i = 0; i < full_extent<T>::value; ++i) {
//		((ElemType)arr)[i] = val;
//	}
//}
