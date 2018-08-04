#include "stdafx.h"
#include "CppUnitTest.h"

#include "../chunk_search/composite_chunk_search.h"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace core::unpacker::certutil;

namespace composite_chunk_search_unit_tests
{
	TEST_CLASS(CompositeChunkSearchTests)
	{
	public:

		TEST_METHOD(composite_chunk_search_returns_match_length_when_one_pattern_is_identical_to_haystack)
		{
			composite_chunk_search<std::string::const_iterator> cs;
			std::string pattern1{ "abc" };
			cs.add_pattern(pattern1);
			std::string pattern2{ "bcd" };
			cs.add_pattern(pattern2);

			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.first);
		}

		TEST_METHOD(composite_chunk_search_returns_match_length_0_when_none_of_patterns_is_identical_to_haystack)
		{
			composite_chunk_search<std::string::const_iterator> cs;
			std::string pattern1{ "abc" };
			cs.add_pattern(pattern1);
			std::string pattern2{ "bcd" };
			cs.add_pattern(pattern2);
			std::string pattern3{ "cde" };
			cs.add_pattern(pattern3);

			std::string haystack{ "cbc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(0), found.first);
		}

		TEST_METHOD(composite_chunk_search_returns_match_length_when_one_of_patterns_is_part_of_haystack)
		{
			composite_chunk_search<std::string::const_iterator> cs;
			std::string pattern1{ "abc" };
			cs.add_pattern(pattern1);
			std::string pattern2{ "bcd" };
			cs.add_pattern(pattern2);
			std::string pattern3{ "cde" };
			cs.add_pattern(pattern3);

			std::string haystack{ "bcabcde" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.first);
		}

		TEST_METHOD(composite_chunk_search_returns_iterator_to_end_of_found_when_one_of_patterns_is_part_of_haystack)
		{
			composite_chunk_search<std::string::const_iterator> cs;
			std::string pattern1{ "abc" };
			cs.add_pattern(pattern1);
			std::string pattern2{ "bcd" };
			cs.add_pattern(pattern2);
			std::string pattern3{ "cde" };
			cs.add_pattern(pattern3);

			std::string haystack{ "bcabcde" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(5), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(composite_chunk_search_returns_match_length_of_found_when_one_of_patterns_is_part_of_haystack)
		{
			composite_chunk_search<std::string::const_iterator> cs;
			std::string pattern1{ "abc" };
			cs.add_pattern(pattern1);
			std::string pattern2{ "bcag" };
			cs.add_pattern(pattern2);
			std::string pattern3{ "bcde" };
			cs.add_pattern(pattern3);
			std::string pattern4{ "cac" };
			cs.add_pattern(pattern4);

			std::string haystack{ "bcabcde" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(5), long(std::distance(haystack.cbegin(), found.second)));
			Assert::AreEqual(size_t(3), found.first);
		}
	};
}