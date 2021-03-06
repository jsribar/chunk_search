// chopped_search.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "chunk_search.h"
#include "composite_chunk_search.h"

#include <array>
#include <iostream>
#include <string>

void print_search(const std::string& pattern)
{
	std::cout << "searching for '" << pattern << "'..." << std::endl;
}

template <typename C>
void print_search(const C& patterns)
{
	std::cout << "searching for: " << std::endl;
	for (const auto& pattern : patterns)
		std::cout << " '" << pattern << "'" << std::endl;
}

void print_result(const std::string& haystack, chunk_search_result<std::string::const_iterator>& result)
{
	if (result.match_length == 0)
		std::cout << "...search in sequence '" << haystack << "' failed" << std::endl;
	else
		std::cout << "...end of pattern found in sequence '" << haystack << "' at position: " << long(result.end - haystack.begin()) << ", match length: " << result.match_length << std::endl;
}

int main()
{
	std::cout << "single pattern search:" << std::endl;

	std::string pattern{ "cde" };
	chunk_search<> cs(pattern);
	print_search(pattern);

	std::string haystack1{ "abc" };
	auto result = cs.search(haystack1.cbegin(), haystack1.cend());
	print_result(haystack1, result);

	std::string haystack2{ "def" };
	result = cs.search(haystack2.cbegin(), haystack2.cend());
	print_result(haystack2, result);

    cs = chunk_search<>("bcd");
    std::cout << "\nrepeat for 'bcd'..." << std::endl;

    result = cs.search(haystack1.cbegin(), haystack1.cend());
    print_result(haystack1, result);

    result = cs.search(haystack2.cbegin(), haystack2.cend());
    print_result(haystack2, result);

    std::cout << "\nmultiple pattern search:" << std::endl;

    std::array<std::string, 4> patterns{ "cde", "cdef", "bcd", "bcde" };
    composite_chunk_search<> ccs{ "cde", "cdef", "bcd", "bcde" };
	print_search(patterns);

	result = ccs.search(haystack1.cbegin(), haystack1.cend());
	print_result(haystack1, result);

	result = ccs.search(haystack2.cbegin(), haystack2.cend());
	print_result(haystack2, result);

    std::cout << "\nrepeat without 'bcd'..." << std::endl;
    ccs = composite_chunk_search<>{ "cde", "cdef", "bcde" };

    result = ccs.search(haystack1.cbegin(), haystack1.cend());
    print_result(haystack1, result);

    result = ccs.search(haystack2.cbegin(), haystack2.cend());
    print_result(haystack2, result);

    return 0;
}

