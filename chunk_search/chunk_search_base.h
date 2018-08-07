#pragma once


template <typename Derived, typename T = std::string>
class chunk_search_base
{
public:
    virtual ~chunk_search_base() = default;

    template <typename ForwardIterator>
    std::pair<size_t, ForwardIterator> search(ForwardIterator haystack_first, ForwardIterator haystack_last)
    {
        Derived& derived = static_cast<Derived&>(*this);
        return derived::search(haystack_first, haystack_last);
    }
};
