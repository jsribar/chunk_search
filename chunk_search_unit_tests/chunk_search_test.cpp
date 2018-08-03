#include "stdafx.h"
#include "CppUnitTest.h"

#include "../chunk_search/chunk_search.h"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace core::unpacker::certutil;

namespace chunk_search_unit_tests
{		
	TEST_CLASS(ChunkSearchTsets)
	{
	public:
		
		TEST_METHOD(chunk_search_returns_true_when_pattern_is_identical_to_haystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsTrue(found.first);
		}

		TEST_METHOD(chunk_search_returns_iterator_to_end_of_found_when_pattern_is_identical_to_haystack)
		{
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "abc" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsTrue(found.second == haystack.cend());
		}

		TEST_METHOD(chunk_search_returns_match_length_3_when_is_identical_to_haystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), cs.match_length());
		}

		TEST_METHOD(chunk_search_return_true_when_pattern_is_a_part_of_haystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "01abc23" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsTrue(found.first);
		}

		TEST_METHOD(chunk_search_return_iterator_to_end_of_found_when_pattern_is_a_part_of_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "01abc23" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(long(5), long(std::distance(haystack.cbegin(), found.second)));
		}

        TEST_METHOD(chunk_search_returns_match_length_when_pattern_is_a_part_of_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern };
            std::string haystack{ "01abc23" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), cs.match_length());
		}

		TEST_METHOD(chunk_search_returns_true_when_pattern_is_a_part_of_haystack_precedeed_with_partial_match)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "ababc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsTrue(found.first);
		}
		
		TEST_METHOD(chunk_search_returns_iterator_to_end_of_found_when_pattern_is_a_part_of_haystack_precedeed_with_partial_match)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "ababc" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(long(5), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(chunk_search_returns_match_length_when_pattern_is_a_part_of_haystack_precedeed_with_partial_match)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "ababc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), cs.match_length());
		}
		
		TEST_METHOD(chunk_search_returns_false_if_pattern_is_not_found)
		{
			std::string pattern{ "abd" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsFalse(found.first);
		}

		TEST_METHOD(chunk_search_returns_iterators_to_haystack_end_if_pattern_is_not_found)
        {
            std::string pattern{ "abd" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "abc" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsTrue(found.second == haystack.cend());
		}

		TEST_METHOD(chunk_search_returns_false_if_only_a_part_of_pattern_is_found)
		{
			std::string pattern{ "012ab" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "012" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsFalse(found.first);
		}

		TEST_METHOD(chunk_search_returns_iterator_to_haystack_end_if_only_a_part_of_pattern_is_found)
        {
            std::string pattern{ "012ab" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "012" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsTrue(found.second == haystack.cend());
		}

        TEST_METHOD(chunk_search_returns_true_after_second_call_when_pattern_is_a_part_of_second_haystack_section)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "0123" };
			auto found1 = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsFalse(found1.first);

            haystack = "012abcd";
            auto found2 = cs.search(haystack.cbegin(), haystack.cend());
            Assert::IsTrue(found2.first);
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

		TEST_METHOD(chunk_search_returns_match_length_after_second_call_when_pattern_is_a_part_of_second_haystack_section)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "0123" };
			cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(0), cs.match_length());

			haystack = "012abc";
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), cs.match_length());
		}

		TEST_METHOD(chunk_search_returns_true_after_second_call_when_pattern_is_split_between_first_and_second_haystack_sections)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "a" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsFalse(found.first);

            haystack = "bc";
            found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::IsTrue(found.first);
        }

		TEST_METHOD(chunk_search_returns_match_length_after_second_call_when_pattern_is_split_between_first_and_second_haystack_sections)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "a" };
			cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(1), cs.match_length());

			haystack = "bc";
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), cs.match_length());
		}

		TEST_METHOD(chunk_search_returns_true_after_second_call_when_partial_pattern_is_split_between_first_and_second_haystack_sections_but_is_in_second_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "a" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsFalse(found.first);

            haystack = "bdabcd";
            found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::IsTrue(found.first);
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

		TEST_METHOD(chunk_search_returns_match_length_after_second_call_when_partial_pattern_is_split_between_first_and_second_haystack_sections_but_is_in_second_haystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "a" };
			cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(1), cs.match_length());

			haystack = "bdabcd";
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), cs.match_length());
		}

        TEST_METHOD(chunk_search_returns_true_after_second_call_when_pattern_is_in_second_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "ab" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::IsFalse(found.first);

            haystack = "abcd";
            found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::IsTrue(found.first);
        }

		TEST_METHOD(chunk_search_returns_iterator_to_end_of_found_after_second_call_when_pattern_is_in_second_haystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "ab" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "abcd";
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(long(3), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(chunk_search_returns_match_length_after_second_call_when_pattern_is_in_second_haystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "ab" };
			cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(2), cs.match_length());

			haystack = "abc";
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), cs.match_length());
		}
		
		TEST_METHOD(chunk_search_returns_true_after_second_call_when_pattern_is_in_second_haystack_but_no_match_in_first_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "def" };
            cs.search(haystack.cbegin(), haystack.cend());

            haystack = "abc";
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::IsTrue(found.first);
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

		TEST_METHOD(chunk_search_returns_match_length_after_second_call_when_pattern_is_in_second_haystack_but_no_match_in_first_haystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "def" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "abc";
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), cs.match_length());
		}
		
		TEST_METHOD(chunk_search_returns_true_after_third_call_when_pattern_is_split_between_three_haystack_sections)
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
            Assert::IsTrue(found.first);
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

		TEST_METHOD(chunk_search_returns_match_length_after_third_call_when_pattern_is_split_between_three_haystack_sections)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
			std::string haystack{ "ddda" };
			cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(1), cs.match_length());

			haystack = "b";
			cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(2), cs.match_length());

			haystack = "c";
			auto found = cs.search(haystack.cbegin(), haystack.cend());
			Assert::AreEqual(size_t(3), cs.match_length());
		}

		TEST_METHOD(chunk_search_reverse_returns_true_when_pattern_is_identical_to_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_reverse_iterator> cs{ pattern.crbegin(), pattern.crend() };
            std::string haystack{ "abc" };
            auto found = cs.search(haystack.crbegin(), haystack.crend());
            Assert::IsTrue(found.first);
        }

        TEST_METHOD(chunk_search_reverse_returns_true_when_pattern_is_a_part_of_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_reverse_iterator> cs{ pattern.crbegin(), pattern.crend() };
            std::string haystack{ "01abc23" };
            auto found = cs.search(haystack.crbegin(), haystack.crend());
            Assert::IsTrue(found.first);
        }
 
        TEST_METHOD(chunk_search_reverse_returns_true_after_third_call_when_pattern_is_split_between_three_haystack_sections)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_reverse_iterator> cs{ pattern.crbegin(), pattern.crend() };
            std::string haystack{ "cd" };
			auto found = cs.search(haystack.crbegin(), haystack.crend());
			Assert::IsFalse(found.first);

            haystack = "b";
            found = cs.search(haystack.crbegin(), haystack.crend());
            Assert::IsFalse(found.first);

            haystack = "a";
            found = cs.search(haystack.crbegin(), haystack.crend());
            Assert::IsTrue(found.first);
        }
   };
}