#pragma once

template <class SumType, class InputIterator>
SumType fn_sum(InputIterator first, InputIterator last)
{
	SumType sum_val = {};

	while (first != last) {
		sum_val += *first;
		++first;
	}

	return sum_val;
}

template <class SumType, class InputIterator, class MapOp>
SumType fn_sum(InputIterator first, InputIterator last, MapOp mapOp)
{
	SumType sum_val = {};

	while (first != last) {
		sum_val += mapOp(*first);
		++first;
	}

	return sum_val;
}

template <class SumType, class Sequence>
SumType fn_seq_sum(const Sequence& seq)
{
	return fn_sum<SumType>(seq.cbegin(), seq.cend());
}

template <class SumType, class Sequence, class MapOp>
SumType fn_seq_sum(const Sequence& seq, MapOp mapOp)
{
	return fn_sum<SumType>(seq.cbegin(), seq.cend(), mapOp);
}

template <class F, class T, size_t... Is>
auto call_unpack_impl(F f, T t, std::index_sequence<Is...>) {
	return f(std::get<Is>(t)...);
}

template <class F, class T>
auto call_unpack(F f, T t) {
	return call_unpack_impl(f, t, std::make_index_sequence<std::tuple_size<T>::value>());
}

template<typename T>
struct function_traits;

template<typename R, typename ...Args>
struct function_traits<R(Args...)>
{
	static const size_t nargs = sizeof...(Args);

	typedef R result_type;
	typedef std::tuple<Args...> args_tuple_type;

	template <size_t i>
	struct arg
	{
		typedef typename std::tuple_element<i, args_tuple_type>::type type;
	};
};
