#pragma once

#include "chunk_search.h"

namespace core { namespace unpacker { namespace certutil {


template <typename ForwardIterator1>
class chunk_search_composite

public:
	void add_pattern(ForwardIterator1 pattern_first, ForwardIterator1 pattern_last)
	{
		patterns.emplace(pattern_first, pattern_last);
	}

	template <typename ForwardIterator2>
	std::pair<ForwardIterator2, ForwardIterator2> search(ForwardIterator2 haystack_first, ForwardIterator2 haystack_last)
	{
		for (auto patern : paterns_m)
		{
			auto result = patern.search(haystack_first, haystack_first);
		}
		// if search pattern is empty, return immediately
		if (pattern_first_m == pattern_last_m)
			return std::make_pair(haystack_first, haystack_first);
		return partial_search(haystack_first, haystack_last);
	}


private:
	list<chunk_search<ForwardIterator1>> paterns_m;



} } } // namespace core::unpacker::certutil
