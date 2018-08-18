#include <algorithm>
#include <functional>
#include <iterator>
#include <utility>
#include <vector>

namespace Algorithmic {
	/*
	template <typename BidirectionalIterator>
	constexpr void insertion_sort(
		BidirectionalIterator first,
		BidirectionalIterator last
	);
	template <typename BidirectionalIterator, typename Compare>
	constexpr void insertion_sort(
		BidirectionalIterator first,
		BidirectionalIterator last,
		Compare compare
	);
	Effects:
		Sorts the elements in the range [first, last).
	Complexity: жи(n^2) comparisons, where n = (last - first)
	*/
	template <typename Bi, typename Func = std::less<>>
	constexpr void insertion_sort(Bi first, Bi last, Func func = {})
	{
		for (Bi it = std::prev(last); it != first;) {
			typename std::iterator_traits<Bi>::value_type key = std::move(*--it);
			Bi it2 = it;
			while (++it2 != last && func(*it2, key)) {
				*std::prev(it2) = std::move(*it2);
			}
			*std::prev(it2) = std::move(key);
		}
	}
	/*
	Complexity:
		Best-case: жи(n)
		Worst-case: жи(n^2)
	*/
	template <typename For, typename Func = std::less<>>
	constexpr void selection_sort(For first, For last, Func func = {})
	{
		for (; first != last; ++first) {
			//Loop invariant: [first(arg), first(var)) consists of
			//the minimum (first(var) - first(arg)) elements sorted
			std::iter_swap(first, std::min_element(first, last, func));
		}
	}

	namespace sort_details {
		template <typename Ran, typename Func, typename Alloc>
		constexpr void merge(Ran first, Ran middle, Ran last, Func func, Alloc alloc)
		{
			using ValT = typename std::iterator_traits<Ran>::value_type;
			std::vector<ValT, Alloc> left{
				std::make_reverse_iterator(std::make_move_iterator(middle)),
				std::make_reverse_iterator(std::make_move_iterator(first)),
				alloc
			}, right{
				std::make_reverse_iterator(std::make_move_iterator(last)),
				std::make_reverse_iterator(std::make_move_iterator(middle)),
				alloc
			};
			auto leftit = left.rbegin(), rightit = right.rbegin();
			for (; first != last; ++first) {
				if (left.empty()) {
					std::move(right.rbegin(), right.rend(), first);
					return;
				}
				if (right.empty()) {
					std::move(left.rbegin(), left.rend(), first);
					return;
				}
				if (func(*leftit, *rightit))
					*first = std::move(*leftit),
					left.pop_back(),
					leftit = left.rbegin();
				else
					*first = std::move(*rightit),
					right.pop_back(),
					rightit = right.rbegin();
			}
		}
	}

	template <typename Ran, typename Func = std::less<>,
		typename Alloc = std::allocator<typename std::iterator_traits<Ran>::value_type>>
	constexpr void merge_sort(Ran first, Ran last, Func func = {}, Alloc alloc = {})
	{
		if (last - first >= 2) {
			auto middle = first + (last - first) / 2;
			merge_sort(first, middle, func, alloc);
			merge_sort(middle, last, func, alloc);
			sort_details::merge(first, middle, last, func, alloc);
		}
	}
}