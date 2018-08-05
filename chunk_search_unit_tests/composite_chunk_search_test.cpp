#include "stdafx.h"
#include "CppUnitTest.h"

#include "../chunk_search/composite_chunk_search.h"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace core::unpacker::certutil;

namespace composite_chunk_search_unit_tests
{
	TEST_CLASS(CompositeChunkSearch)
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

		TEST_METHOD(composite_chunk_search_returns_match_length_0_when_none_of_patterns_is_found_in_haystack)
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

			Assert::AreEqual(size_t(3), found.first);
			Assert::AreEqual(long(5), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(composite_chunk_search_returns_match_length_of_first_pattern_matched_entirely_when_all_patterns_are_part_of_haystack)
		{
			std::string pattern1{ "abcde" };
			std::string pattern2{ "abcd" };
			std::string pattern3{ "bcd" };
			std::string pattern4{ "bcde" };
			composite_chunk_search<std::string::const_iterator> cs;
			cs.add_pattern(pattern1);
			cs.add_pattern(pattern2);
			cs.add_pattern(pattern3);
			cs.add_pattern(pattern4);

			std::string haystack{ "aaabcdef" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(4), found.first);
			Assert::AreEqual(long(6), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(composite_chunk_search_returns_match_length_of_longest_pattern_for_patterns_that_have_same_end)
		{
			std::string pattern1{ "aaabcd" };
			std::string pattern2{ "aabcd" };
			std::string pattern3{ "abcd" };
			composite_chunk_search<std::string::const_iterator> cs;
			cs.add_pattern(pattern1);
			cs.add_pattern(pattern2);
			cs.add_pattern(pattern3);

			std::string haystack{ "aaaabcdef" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(6), found.first);
			Assert::AreEqual(long(7), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(composite_chunk_search_returns_match_length_of_longest_pattern_for_patterns_that_have_same_end_when_patterns_are_split_in_2_haystacks_is_)
		{
			std::string pattern1{ "aaabcd" };
			std::string pattern2{ "aabcd" };
			std::string pattern3{ "abcd" };
			composite_chunk_search<std::string::const_iterator> cs;
			cs.add_pattern(pattern1);
			cs.add_pattern(pattern2);
			cs.add_pattern(pattern3);

			std::string haystack{ "aa" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			haystack = "abcdef";
			found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(6), found.first);
			Assert::AreEqual(long(4), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(composite_chunk_search_returns_match_length_when_the_only_pattern_is_identical_to_haystack)
		{
			composite_chunk_search<std::string::const_iterator> cs;
			std::string pattern{ "abc" };
			cs.add_pattern(pattern);

			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.first);
		}

		TEST_METHOD(composite_chunk_search_returns_match_length_0_when_the_only_patterns_is_found_in_haystack)
		{
			composite_chunk_search<std::string::const_iterator> cs;
			std::string pattern{ "abc" };
			cs.add_pattern(pattern);

			std::string haystack{ "cbc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(0), found.first);
		}

	};
}