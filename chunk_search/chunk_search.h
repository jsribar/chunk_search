/*
	Copyright(c) 2018 Julijan Sribar julijan(dot)sribar(at)gmail(dot)com

	This software is provided 'as-is', without any express or implied
	warranty.In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions :

	1. The origin of this software must not be misrepresented; you must not
	   claim that you wrote the original software.If you use this software
	   in a product, an acknowledgment in the product documentation would be
	   appreciated but is not required.
	2. Altered source versions must be plainly marked as such, and must not be
	   misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
*/

#pragma once

#include <string>

template <typename ForwardIterator>
struct chunk_search_result
{
    size_t match_length;
    ForwardIterator start;
    ForwardIterator end;

    chunk_search_result(size_t ml, ForwardIterator start, ForwardIterator end)
        : match_length(ml)
        , start(start)
        , end(end)
    {}
};

// utility class that allows to search for a pattern across several chunks
template <typename T = std::string>
class chunk_search
{
public:
	chunk_search(T pattern)
		: pattern_m{ std::move(pattern) }
		, partial_match_end_m{ pattern_m.begin() }
	{}

	chunk_search(chunk_search<T>&& search)
	{
		std::swap(pattern_m, search.pattern_m);
		partial_match_end_m = pattern_m.begin();
	}

	chunk_search& operator=(chunk_search<T>&& search)
	{
		std::swap(pattern_m, search.pattern_m);
		partial_match_end_m = pattern_m.begin();
		match_length_m = 0;
		return *this;
	}

	// disable copying
	chunk_search(const chunk_search<T>&) = delete;
	chunk_search& operator=(const chunk_search<T>&) = delete;

	template <typename ForwardIterator>
    chunk_search_result<ForwardIterator> search(ForwardIterator haystack_first, ForwardIterator haystack_last)
	{
		// if search pattern is empty, return immediately
		if (pattern_m.begin() == pattern_m.end())
            return chunk_search_result<ForwardIterator>{ 0, haystack_first, haystack_first };
		return partial_search(haystack_first, haystack_last);
	}

private:
	T pattern_m;
	typename T::const_iterator partial_match_end_m;
	size_t match_length_m{ 0 };

	template <typename ForwardIterator>
    chunk_search_result<ForwardIterator> partial_search(ForwardIterator haystack_first, ForwardIterator haystack_last)
	{
		while (haystack_first != haystack_last)
		{
			ForwardIterator haystack_it = haystack_first;
			typename T::const_iterator pattern_it = partial_match_end_m;
			while (*haystack_it == *pattern_it)
			{
                ForwardIterator found_haystack = haystack_it;
				++pattern_it;
				++haystack_it;
				++match_length_m;
				if (pattern_it == pattern_m.end())
				{
                    const auto& result = chunk_search_result<ForwardIterator>{ match_length_m, haystack_first, haystack_it };
					partial_match_end_m = pattern_m.begin(); // reset if someone wants to continue the search
					match_length_m = 0;
					return result;
				}
				if (haystack_it == haystack_last)
				{
					partial_match_end_m = pattern_it; // partial match, remember where stopped to continue on in the next chunk
                    return chunk_search_result<ForwardIterator>{ 0, found_haystack, haystack_last };
				}
			}
			// if a part was found in previous haystack, then matching part of previous haystack is actually in search pattern
			// so start the search inside the pattern
			if (match_length_m > size_t(haystack_it - haystack_first))
			{
				if (search_inside_pattern())
					continue;
			}
			if (partial_match_end_m == pattern_m.begin())
				++haystack_first;
			partial_match_end_m = pattern_m.begin();
			match_length_m = 0;
		}
        return chunk_search_result<ForwardIterator>{ 0, haystack_last, haystack_last };
	}

	bool search_inside_pattern()
	{
		// start search from second position...
		typename T::const_iterator search_from_it = pattern_m.begin() + 1;
		// ...up to item found in previous haystack
		while (search_from_it != partial_match_end_m)
		{
			typename T::const_iterator pattern_it = pattern_m.begin();
			match_length_m = 0;
			while (*pattern_it == *search_from_it)
			{
				++pattern_it;
				++search_from_it;
				++match_length_m;
				// reached the end of search successfully
				if (search_from_it == partial_match_end_m)
				{
					partial_match_end_m = pattern_it;
					return true;
				}
			}
			++search_from_it;
		}
		return false;
	}
};
