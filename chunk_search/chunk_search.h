#pragma once

#include <utility>
#include <string>

namespace core { namespace unpacker { namespace certutil {

// utility class that allows to search for a pattern across several chunks
template <typename ForwardIterator1>
class chunk_search
{
public:
    chunk_search(ForwardIterator1 pattern_first, ForwardIterator1 pattern_last)
        : pattern_first_m(pattern_first)
        , pattern_last_m(pattern_last)
        , search_pattern_m(pattern_first)
    {}

    template <typename T>
    chunk_search(T& pattern)
        : pattern_first_m(pattern.cbegin())
        , pattern_last_m(pattern.cend())
        , search_pattern_m(pattern.cbegin())
    {}

	// prevent passing temporary objects
	template <typename T>
	explicit chunk_search(T&& pattern) = delete;

    template <typename ForwardIterator2>
    std::pair<size_t, ForwardIterator2> search(ForwardIterator2 haystack_first, ForwardIterator2 haystack_last)
    {
        // if search pattern is empty, return immediately
        if (pattern_first_m == pattern_last_m)
            return std::make_pair(0, haystack_first);
        return partial_search(haystack_first, haystack_last);
    }

private:
	const ForwardIterator1 pattern_first_m;
    const ForwardIterator1 pattern_last_m;
    ForwardIterator1 search_pattern_m;
	size_t match_length_m{ 0 };

    template <typename ForwardIterator2>
    std::pair<size_t, ForwardIterator2> partial_search(ForwardIterator2 haystack_first, ForwardIterator2 haystack_last)
    {
		while (haystack_first != haystack_last)
        {
            ForwardIterator2 haystack_it = haystack_first;
            ForwardIterator1 pattern_it = search_pattern_m;
            while (*haystack_it == *pattern_it)
            {
                ++pattern_it;
                ++haystack_it;
				++match_length_m;
                if (pattern_it == pattern_last_m)
                {
                    search_pattern_m = pattern_first_m; // reset to the start (if someone wants to continue the search)
                    return std::make_pair(match_length_m, haystack_it);
                }
                if (haystack_it == haystack_last)
                {
                    search_pattern_m = pattern_it; // partial match, remember where stopped to continue on in the next chunk
                    return std::make_pair(0, haystack_last);
                }
            }
			// if a part was found in previous haystack, then matching part of previous haystack is actually in search pattern
			// so start the search inside the pattern
			if (match_length_m > size_t(haystack_it - haystack_first))
			{
				if (search_inside_pattern())
					continue;
			}
			if (search_pattern_m == pattern_first_m)
				++haystack_first;
			search_pattern_m = pattern_first_m;
			match_length_m = 0;
		}
        return std::make_pair(0, haystack_last);
    }

	bool search_inside_pattern()
	{
		// start search from second position...
		ForwardIterator1 search_from_it = pattern_first_m + 1;
		// ...up to item found in previous haystack
		while (search_from_it != search_pattern_m)
		{
			ForwardIterator1 pattern_it = pattern_first_m;
			match_length_m = 0;
			while (*pattern_it == *search_from_it)
			{
				++pattern_it;
				++search_from_it;
				++match_length_m;
				// reached the end of search successfully
				if (search_from_it == search_pattern_m)
				{
					search_pattern_m = pattern_it;
					return true;
				}
			}
			++search_from_it;
		}
		return false;
	}

};

} } } // namespace core::unpacker::certutil

