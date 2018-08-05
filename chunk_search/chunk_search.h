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

#include <utility>
#include <string>

// utility class that allows to search for a pattern across several chunks
template <typename T = std::string>
class chunk_search
{
public:
	chunk_search(typename T::const_iterator pattern_first, typename T::const_iterator pattern_last)
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

    template <typename ForwardIterator>
    std::pair<size_t, ForwardIterator> search(ForwardIterator haystack_first, ForwardIterator haystack_last)
    {
        // if search pattern is empty, return immediately
        if (pattern_first_m == pattern_last_m)
            return std::make_pair(0, haystack_first);
        return partial_search(haystack_first, haystack_last);
    }

private:
	const typename T::const_iterator pattern_first_m;
    const typename T::const_iterator pattern_last_m;
	typename T::const_iterator search_pattern_m;
	size_t match_length_m{ 0 };

    template <typename ForwardIterator>
    std::pair<size_t, ForwardIterator> partial_search(ForwardIterator haystack_first, ForwardIterator haystack_last)
    {
		while (haystack_first != haystack_last)
        {
            ForwardIterator haystack_it = haystack_first;
			typename T::const_iterator pattern_it = search_pattern_m;
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
		typename T::const_iterator search_from_it = pattern_first_m + 1;
		// ...up to item found in previous haystack
		while (search_from_it != search_pattern_m)
		{
			typename T::const_iterator pattern_it = pattern_first_m;
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
