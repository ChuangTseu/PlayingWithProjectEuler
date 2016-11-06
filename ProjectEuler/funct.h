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
