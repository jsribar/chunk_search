#include "stdafx.h"
#include "CppUnitTest.h"

#include "../chunk_search/chunk_search.h"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace core::unpacker::certutil;

namespace chunk_search_unit_tests
{		
	TEST_CLASS(ChunkSearch)
	{
	public:
		
		TEST_METHOD(chunk_search_returns_match_length_when_is_identical_to_haystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), found.first);
		}

		TEST_METHOD(chunk_search_returns_iterator_to_end_of_found_when_pattern_is_identical_to_haystack)
		{
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "abc" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsTrue(found.second == haystack.cend());
		}

		TEST_METHOD(chunk_search_returns_match_length_when_pattern_is_a_part_of_haystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "01abc23" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), found.first);
		}

		TEST_METHOD(chunk_search_return_iterator_to_end_of_found_when_pattern_is_a_part_of_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "01abc23" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(long(5), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(chunk_search_returns_match_length_when_pattern_is_a_part_of_haystack_precedeed_with_partial_match)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "ababc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), found.first);
		}
		
		TEST_METHOD(chunk_search_returns_iterator_to_end_of_found_when_pattern_is_a_part_of_haystack_precedeed_with_partial_match)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "ababc" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(long(5), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(chunk_search_returns_match_length_0_if_pattern_is_not_found)
		{
			std::string pattern{ "abd" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(0), found.first);
		}

		TEST_METHOD(chunk_search_returns_iterators_to_haystack_end_if_pattern_is_not_found)
        {
            std::string pattern{ "abd" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "abc" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsTrue(found.second == haystack.cend());
		}

		TEST_METHOD(chunk_search_returns_match_length_0_if_only_a_part_of_pattern_is_found)
		{
			std::string pattern{ "012ab" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "012" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(0), found.first);
		}

		TEST_METHOD(chunk_search_returns_iterator_to_haystack_end_if_only_a_part_of_pattern_is_found)
        {
            std::string pattern{ "012ab" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "012" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsTrue(found.second == haystack.cend());
		}

		TEST_METHOD(chunk_search_returns_match_length_after_second_call_when_pattern_is_a_part_of_second_haystack_section)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "0123" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsFalse(found.first);

            haystack = "012abcd";
            found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), found.first);
		}

		TEST_METHOD(chunk_search_returns_iterator_to_end_of_found_after_second_call_when_pattern_is_a_part_of_second_haystack_section)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "0123" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "012abcd";
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(long(6), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(chunk_search_returns_match_length_after_second_call_when_part_of_pattern_is_in_first_haystack_but_pattern_is_part_of_second_haystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "ab" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsFalse(found.first);

			haystack = "abcd";
			found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), found.first);
		}

		TEST_METHOD(chunk_search_returns_iterator_to_end_of_found_after_second_call_when_part_of_pattern_is_in_first_haystack_but_pattern_is_part_of_second_haystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "ab" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "abcd";
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(long(3), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(chunk_search_returns_match_length_after_second_call_when_pattern_is_split_between_first_and_second_haystack_sections)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "a" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsFalse(found.first);

            haystack = "bc";
            found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), found.first);
        }

		TEST_METHOD(chunk_search_returns_iterator_to_end_of_found_after_second_call_when_pattern_is_split_between_first_and_second_haystack_sections)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "a" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			haystack = "bc";
			found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(long(2), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(chunk_search_returns_match_length_after_second_call_when_partial_pattern_is_split_between_first_and_second_haystack_sections_but_is_in_second_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "a" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsFalse(found.first);

            haystack = "bdabcd";
            found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), found.first);
		}

		TEST_METHOD(chunk_search_returns_iterator_to_end_of_found_after_second_call_when_partial_pattern_is_split_between_first_and_second_haystack_sections_but_is_in_second_haystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "a" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsTrue(found.second == haystack.cend());

			haystack = "bdabcd";
			found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(long(5), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(chunk_search_returns_match_length_after_second_call_when_pattern_is_in_second_haystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "ab" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(0), found.first);

			haystack = "abc";
			found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), found.first);
		}
		
		TEST_METHOD(chunk_search_returns_match_length_after_second_call_when_pattern_is_in_second_haystack_but_no_match_in_first_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "def" };
            cs.search(haystack.cbegin(), haystack.cend());

            haystack = "abc";
            auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), found.first);
		}

		TEST_METHOD(chunk_search_returns_iterator_to_end_of_found_after_second_call_when_pattern_is_in_second_haystack_but_no_match_in_first_haystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "def" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "abc";
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsTrue(found.second == haystack.cend());
		}

		TEST_METHOD(chunk_search_returns_tmatch_length_after_third_call_when_pattern_is_split_between_three_haystack_sections)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "da" };
            cs.search(haystack.cbegin(), haystack.cend());

            haystack = "b";
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::IsFalse(found.first);

            haystack = "c";
            found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), found.first);
		}

		TEST_METHOD(chunk_search_returns_iterator_to_end_of_found_after_third_call_when_pattern_is_split_between_three_haystack_sections)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "da" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "b";
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "c";
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsTrue(found.second == haystack.cend());
		}

		TEST_METHOD(chunk_search_returns_match_length_after_second_call_when_repetitive_pattern_is_split_between_two_haystack_sections)
		{
			std::string pattern{ "abac" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "aba" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsFalse(found.first);

			haystack = "bac";
			found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(4), found.first);
		}

		TEST_METHOD(chunk_search_returns_iterator_to_found_after_second_call_when_repetitive_pattern_is_split_between_two_haystack_sections)
		{
			std::string pattern{ "abac" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "aba" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "bac";
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(long(3), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(chunk_search_returns_match_length_after_third_call_when_repetitive_pattern_is_split_between_three_haystack_sections)
		{
			std::string pattern{ "abababc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "aba" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsFalse(found.first);

			haystack = "bab";
			found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsFalse(found.first);

			haystack = "abcd";
			found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(7), found.first);
		}

		TEST_METHOD(chunk_search_returns_iterator_to_found_after_third_call_when_repetitive_pattern_is_split_between_three_haystack_sections)
		{
			std::string pattern{ "abababc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "aba" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "bab";
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "abcd";
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(long(3), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(chunk_search_returns_true_after_third_call_when_repetitive_pattern_is_split_between_two_haystack_sections)
		{
			std::string pattern{ "baba" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "aba" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsFalse(found.first);

			haystack = "bbab";
			found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsFalse(found.first);

			haystack = "abcd";
			found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(4), found.first);
		}

		TEST_METHOD(chunk_search_returns_iterator_to_found_after_third_call_when_repetitive_pattern_is_split_between_two_haystack_sections)
		{
			std::string pattern{ "baba" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "aba" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "bbab";
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "abcd";
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(long(1), long(std::distance(haystack.cbegin(), found.second)));
		}
  };
}