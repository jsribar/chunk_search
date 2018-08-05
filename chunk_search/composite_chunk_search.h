#pragma once

#include "chunk_search.h"

#include <algorithm>
#include <utility>
#include <vector>

namespace core { namespace unpacker { namespace certutil {

template <typename ForwardIterator1>
class composite_chunk_search
{
	using ChunkSearch = chunk_search<ForwardIterator1>;
public:
	composite_chunk_search() = default;

	void add_pattern(ForwardIterator1 pattern_first, ForwardIterator1 pattern_last)
	{
		patterns_m.emplace_back(pattern_first, pattern_last);
	}

	template <typename T>
	void add_pattern(T& pattern)
	{
		patterns_m.emplace_back(pattern);
	}

	// prevent passing temporary objects
	template <typename T>
	void add_pattern(T&& pattern) = delete;

	template <typename ForwardIterator2>
	std::pair<size_t, ForwardIterator2> search(ForwardIterator2 haystack_first, ForwardIterator2 haystack_last)
	{
		std::vector<std::pair<size_t, ForwardIterator2>> successful;
		for (auto& pattern : patterns_m)
		{
			auto result = pattern.search(haystack_first, haystack_last);
			if (result.first > 0)
				successful.push_back(result);
		}
		if (successful.empty())
			return std::make_pair(0, haystack_last);
		// return match that ends foremost and if two end at the same position, return the shorter one
		return *std::min_element(successful.begin(), successful.end(), [&haystack_first](const auto& res1, const auto& res2) 
		{ 
			return res1.second - res2.second ? res1.second < res2.second : res1.first > res2.first;
		});
	}

private:
	std::vector<ChunkSearch> patterns_m;
};

} } } // namespace core::unpacker::certutil
