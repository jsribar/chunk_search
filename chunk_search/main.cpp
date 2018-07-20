// chopped_search.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "chunk_search.h"

#include <iostream>
#include <string>
#include <utility>

namespace cuc = core::unpacker::certutil;

// simple test implementation, according to http://www.cplusplus.com/reference/algorithm/search/
template<class ForwardIterator1, class ForwardIterator2>
std::pair<ForwardIterator1, ForwardIterator2> search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
{
    if (first2 == last2) 
        return std::make_pair(first1, first2);  // specified in C++11

    while (first1 != last1)
    {
        ForwardIterator1 it1 = first1;
        ForwardIterator2 it2 = first2;
        while (*it1 == *it2)
        {
            ++it1;
            ++it2;
            if (it2 == last2)
                return std::make_pair(first1, it2);
            if (it1 == last1)
                return std::make_pair(last1, it2);
        }
        ++first1;
    }
    return std::make_pair(last1, first2);
}

void print_test(const std::string& pattern, const std::string& haystack)
{
    const auto it = search(haystack.cbegin(), haystack.cend(), pattern.cbegin(), pattern.cend());
    bool found = it.first != haystack.cend();
    std::cout << pattern;
    if (!found)
        std::cout << " not";
    std::cout << " found" << " in: " << haystack;
    if (found)
        std::cout << " at : " << static_cast<std::string>(&(*it.first));
    std::cout << std::endl;
}

int main()
{
    print_test("abc", "ab");
    print_test("abc", "abc");
    print_test("abc", "0abc");
    print_test("abc", "abd");
    print_test("abc", "aaaaaabc");
    print_test("abc", "aaaaaabcabcabc");

    return 0;
}

