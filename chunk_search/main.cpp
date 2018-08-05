// chopped_search.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "chunk_search.h"
#include "composite_chunk_search.h"

#include <iostream>
#include <string>
#include <utility>

void print_search(const std::string& pattern)
{
	std::cout << "searching for '" << pattern << "'..." << std::endl;
}

void print_search(std::initializer_list<std::string> patterns)
{
	std::cout << "searching for: " << std::endl;
	for (const auto& pattern : patterns)
		std::cout << " '" << pattern << "'" << std::endl;
}

void print_result(const std::string& haystack, std::pair<size_t, std::string::const_iterator>& result)
{
	if (result.first == 0)
		std::cout << "...search in haystack '" << haystack << "' failed" << std::endl;
	else
		std::cout << "...end of pattern found in haystack '" << haystack << "' at position: " << long(result.second - haystack.begin()) << std::endl;
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


	std::cout << "\nmultiple pattern search:" << std::endl;

	std::string pattern1{ "cde" };
	std::string pattern2{ "cdef" };
	std::string pattern3{ "bcd" };
	std::string pattern4{ "bcde" };
	composite_chunk_search<> ccs;
	print_search({ pattern1, pattern2, pattern3, pattern4 });
	ccs.add_pattern(pattern1);
	ccs.add_pattern(pattern2);
	ccs.add_pattern(pattern3);
	ccs.add_pattern(pattern4);

	result = ccs.search(haystack1.cbegin(), haystack1.cend());
	print_result(haystack1, result);

	result = ccs.search(haystack2.cbegin(), haystack2.cend());
	print_result(haystack2, result);

    return 0;
}

