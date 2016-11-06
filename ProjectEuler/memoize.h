#pragma once

#include <map>
#include <utility>

template <class R, class... Args>
using RecMemoMapT = std::map<std::tuple<Args...>, R>;

template <class R, class... Args>
R fn_memo_wrap(RecMemoMapT<R, Args...>& memo_map, R(*pfn)(RecMemoMapT<R, Args...>&, Args...), Args... args) {
	auto args_tuple = std::make_tuple(args...);

	auto it = memo_map.find(args_tuple);
	if (it != memo_map.end()) return it->second;

	R res = pfn(memo_map, args...);
	memo_map.emplace(args_tuple, res);

	return res;
}
