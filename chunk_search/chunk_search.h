#pragma once

#include <utility>

namespace core { namespace unpacker { namespace certutil {

// utility class that allows to search for a pattern across 
template <typename ForwardIterator1>
class chunk_search
{
public:
    chunk_search(ForwardIterator1 pattern_first, ForwardIterator1 pattern_last)
        : pattern_first_m(pattern_first)
        , pattern_last_m(pattern_last)
        , search_pattern_m(pattern_first)
    {}

    // returns true if pattern was found; in that case second will contain total offset, starting from
    // the first haystack that has been searched for the pattern
    template <typename ForwardIterator2>
    std::pair<bool, size_t> search(ForwardIterator2 haystack_first, ForwardIterator2 haystack_last)
    {
        // if search pattern is empty, return immediately
        if (pattern_first_m == pattern_last_m)
            return std::make_pair(true, 0);

        const auto& result = partial_search(haystack_first, haystack_last);
        return std::make_pair(result != haystack_last, offset_m);
    }

    void reset()
    {
        search_pattern_m = pattern_first_m;
        offset_m = 0;
    }

private:
    ForwardIterator1 pattern_first_m;
    ForwardIterator1 pattern_last_m;
    ForwardIterator1 search_pattern_m;
    size_t offset_m{ 0 };

    template <typename ForwardIterator2>
    ForwardIterator2 partial_search(ForwardIterator2 haystack_first, ForwardIterator2 haystack_last)
    {
        while (haystack_first != haystack_last)
        {
            ForwardIterator2 haystack_it = haystack_first;
            ForwardIterator1 pattern_it = search_pattern_m;
            while (*haystack_it == *pattern_it)
            {
                ++pattern_it;
                if (pattern_it == pattern_last_m)
                {
                    search_pattern_m = pattern_first_m; // reset to the start (if someone wants to search further)
                    return haystack_first;
                }
                ++haystack_it;
                if (haystack_it == haystack_last)
                {
                    search_pattern_m = pattern_it;
                    return haystack_last;
                }
            }
            ++haystack_first;
            ++offset_m;
        }
        search_pattern_m = pattern_first_m;
        return haystack_last;
    }

};

} } } // namespace core::unpacker::certutil

