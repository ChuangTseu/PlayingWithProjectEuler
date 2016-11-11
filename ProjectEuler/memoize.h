#pragma once

#include <map>
#include <unordered_map>
#include <utility>

template <class R, class... Args>
using ManyArgsRecMemoMapT = std::map<std::tuple<Args...>, R>;

template <class R, class Arg>
using SingleArgRecMemoMapT = std::unordered_map<Arg, R>;

// Single arg specialization
template <class R, class Arg>
R fn_memo_wrap(SingleArgRecMemoMapT<R, Arg>& memo_map, R(*rec_pfn)(Arg), Arg arg) {
	auto it = memo_map.find(arg);
	if (it != memo_map.end()) return it->second;

	R res = rec_pfn(arg);
	memo_map.emplace(arg, res);

	return res;
}

template <class R, class... Args>
R fn_memo_wrap(ManyArgsRecMemoMapT<R, Args...>& memo_map, R(*rec_pfn)(Args...), Args... args) {
	auto args_tuple = std::make_tuple(args...);

	auto it = memo_map.find(args_tuple);
	if (it != memo_map.end()) return it->second;

	R res = rec_pfn(args...);
	memo_map.emplace(args_tuple, res);

	return res;
}

template <class R, class... Args>
R fn_memo_wrap_rec(ManyArgsRecMemoMapT<R, Args...>& memo_map, R(*rec_pfn)(ManyArgsRecMemoMapT<R, Args...>&, Args...), Args... args) {
	auto args_tuple = std::make_tuple(args...);

	auto it = memo_map.find(args_tuple);
	if (it != memo_map.end()) return it->second;

	R res = rec_pfn(memo_map, args...);
	memo_map.emplace(args_tuple, res);

	return res;
}
