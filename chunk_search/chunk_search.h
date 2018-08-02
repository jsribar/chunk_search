#pragma once

#include <utility>

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
    chunk_search(const T& pattern)
        : pattern_first_m(std::begin(pattern))
        , pattern_last_m(std::end(pattern))
        , search_pattern_m(std::begin(pattern))
    {}

    template <typename ForwardIterator2>
    std::pair<ForwardIterator2, ForwardIterator2> search(ForwardIterator2 haystack_first, ForwardIterator2 haystack_last)
    {
        // if search pattern is empty, return immediately
        if (pattern_first_m == pattern_last_m)
            return std::make_pair(haystack_first, haystack_first);
        return partial_search(haystack_first, haystack_last);
    }

    // total offset from the first chunk
    size_t total_offset() const noexcept
    {
        return total_offset_m;
    }

private:
    ForwardIterator1 pattern_first_m;
    ForwardIterator1 pattern_last_m;
    ForwardIterator1 search_pattern_m;
    size_t total_offset_m{ 0 };

    template <typename ForwardIterator2>
    std::pair<ForwardIterator2, ForwardIterator2> partial_search(ForwardIterator2 haystack_first, ForwardIterator2 haystack_last)
    {
        while (haystack_first != haystack_last)
        {
            ForwardIterator2 haystack_it = haystack_first;
            ForwardIterator1 pattern_it = search_pattern_m;
            while (*haystack_it == *pattern_it)
            {
                ++pattern_it;
                ++haystack_it;
                if (pattern_it == pattern_last_m)
                {
                    search_pattern_m = pattern_first_m; // reset to the start (if someone wants to continue the search)
                    return std::make_pair(haystack_first, haystack_it);
                }
                if (haystack_it == haystack_last)
                {
                    search_pattern_m = pattern_it; // partial match, remember where stopped to continue on in the next chunk
                    return std::make_pair(haystack_last, haystack_last);
                }
            }
            ++haystack_first;
            ++total_offset_m;
        }
        search_pattern_m = pattern_first_m;
        return std::make_pair(haystack_last, haystack_last);
    }

};

} } } // namespace core::unpacker::certutil

