namespace Algorithmic {
	/*
	template <typename InputIterator, typename T>
	constexpr InputIterator linear_search(
		InputIterator first,
		InputIterator last,
		const T& value
	);

	Returns:
		The first iterator i in the range [first, last) such that (*i == value).
		Returns last if no such iterator is found.
	Complexity:	жи(n) comparisons for equality, where n = (last - first)
		Best-case: 1 comparison for equality
		Worst-case: (last-first) comparisons for equality
		Average-case: (last-first+1)/2 comparisons for equality
	*/
	template <typename In, typename T>
	constexpr In linear_search(In first, In last, const T& value)
	{
		while (first != last && *first != value)
			//loop invariant: [first(arg), first(var)) does not contain any element equal to (value)
			++first;
		return first;
	}

	template <typename Ran, typename T, typename Func = std::less<>>
	constexpr Ran binary_search(Ran first, Ran last, const T& value, Func func = {})
	{
		Ran original_last = last;
		while (first != last) {
			Ran middle = first + (last - first) / 2;
			if (func(value, *middle))
				last = middle;
			else if (func(*middle, value))
				first = middle;
			else
				return middle;
		}		
		return original_last;
	}
}