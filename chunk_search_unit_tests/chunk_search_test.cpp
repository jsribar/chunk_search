#include "stdafx.h"
#include "CppUnitTest.h"

#include "../chunk_search/chunk_search.h"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace core::unpacker::certutil;

namespace chunk_search_unit_tests
{		
	TEST_CLASS(UnitTest1)
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

        TEST_METHOD(chunk_search_returns_offset_0_is_identical_to_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "abc" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::AreEqual(size_t(0), found.second);
        }

        TEST_METHOD(chunk_search_returns_true_when_pattern_is_a_part_of_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "01abc23" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::IsTrue(found.first);
        }

        TEST_METHOD(chunk_search_returns_offset_when_pattern_is_a_part_of_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "01abc23" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::AreEqual(size_t(2), found.second);
        }

        TEST_METHOD(chunk_search_returns_true_when_pattern_is_a_part_of_haystack_precedeed_with_partial_match)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "ababc" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::IsTrue(found.first);
        }

        TEST_METHOD(chunk_search_returns_offset_when_pattern_is_a_part_of_haystack_precedeed_with_partial_match)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "ababc" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::AreEqual(size_t(2), found.second);
        }
        TEST_METHOD(chunk_search_returns_false_if_pattern_is_not_found)
        {
            std::string pattern{ "abd" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "abc" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::IsFalse(found.first);
        }

        TEST_METHOD(chunk_search_returns_false_if_only_a_part_of_pattern_is_found)
        {
            std::string pattern{ "012ab" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "012" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::IsFalse(found.first);
        }

        TEST_METHOD(chunk_search_returns_true_after_second_call_when_pattern_is_a_part_of_second_haystack_section)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "0123" };

            haystack = "012abc";
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::IsTrue(found.first);
        }

        TEST_METHOD(chunk_search_returns_total_offset_after_second_call_when_pattern_is_a_part_of_second_haystack_section)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "0123" };
            cs.search(haystack.cbegin(), haystack.cend());

            haystack = "012abc";
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::AreEqual(size_t(7), found.second);
        }

        TEST_METHOD(chunk_search_returns_true_after_second_call_when_pattern_is_split_between_first_and_second_haystack_sections)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "a" };
            cs.search(haystack.cbegin(), haystack.cend());

            haystack = "bc";
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::IsTrue(found.first);
        }

        TEST_METHOD(chunk_search_returns_total_offset_after_second_call_when_pattern_is_split_between_first_and_second_haystack_sections)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "a" };
            cs.search(haystack.cbegin(), haystack.cend());

            haystack = "bc";
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::AreEqual(size_t(0), found.second);
        }

        TEST_METHOD(chunk_search_returns_true_after_second_call_when_partial_pattern_is_split_between_first_and_second_haystack_sections_but_is_in_second_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "a" };
            cs.search(haystack.cbegin(), haystack.cend());

            haystack = "bdabc";
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::IsTrue(found.first);
        }

        TEST_METHOD(chunk_search_returns_total_offset_after_second_call_when_partial_pattern_is_split_between_first_and_second_haystack_sections_but_is_in_second_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "a" };
            cs.search(haystack.cbegin(), haystack.cend());

            haystack = "bdabc";
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::AreEqual(size_t(3), found.second);
        }

        TEST_METHOD(chunk_search_returns_true_after_second_call_when_pattern_is_in_second_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "ab" };
            cs.search(haystack.cbegin(), haystack.cend());

            haystack = "abc";
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::IsTrue(found.first);
        }

        TEST_METHOD(chunk_search_returns_offset_after_second_call_when_pattern_is_in_second_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "ab" };
            cs.search(haystack.cbegin(), haystack.cend());

            haystack = "abc";
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::AreEqual(size_t(2), found.second);
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

        TEST_METHOD(chunk_search_returns_offset_after_second_call_when_pattern_is_in_second_haystack_but_no_match_in_first_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "def" };
            cs.search(haystack.cbegin(), haystack.cend());

            haystack = "abc";
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::AreEqual(size_t(3), found.second);
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

        TEST_METHOD(chunk_search_returns_total_offset_after_third_call_when_pattern_is_split_between_three_haystack_sections)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };
            std::string haystack{ "ddda" };
            cs.search(haystack.cbegin(), haystack.cend());

            haystack = "b";
            cs.search(haystack.cbegin(), haystack.cend());

            haystack = "c";
            auto found = cs.search(haystack.cbegin(), haystack.cend());
            Assert::AreEqual(size_t(3), found.second);
        }

        TEST_METHOD(chunk_search_reverse_returns_true_when_pattern_is_identical_to_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_reverse_iterator> cs{ pattern.crbegin(), pattern.crend() };
            std::string haystack{ "abc" };
            auto found = cs.search(haystack.crbegin(), haystack.crend());
            Assert::IsTrue(found.first);
        }

        TEST_METHOD(chunk_search_reverse_returns_offset_0_is_identical_to_haystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_reverse_iterator> cs{ pattern.crbegin(), pattern.crend() };
            std::string haystack{ "abc" };
            auto found = cs.search(haystack.crbegin(), haystack.crend());
            Assert::AreEqual(size_t(0), found.second);
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
            cs.search(haystack.crbegin(), haystack.crend());

            haystack = "b";
            auto found = cs.search(haystack.crbegin(), haystack.crend());
            Assert::IsFalse(found.first);

            haystack = "a";
            found = cs.search(haystack.crbegin(), haystack.crend());
            Assert::IsTrue(found.first);
        }

        TEST_METHOD(chunk_search_reverse_returns_offset_1_after_third_call_when_pattern_is_split_between_three_haystack_sections)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_reverse_iterator> cs{ pattern.crbegin(), pattern.crend() };
            std::string haystack{ "cd" };
            cs.search(haystack.crbegin(), haystack.crend());

            haystack = "b";
            auto found = cs.search(haystack.crbegin(), haystack.crend());
            Assert::IsFalse(found.first);

            haystack = "a";
            found = cs.search(haystack.crbegin(), haystack.crend());
            Assert::AreEqual(size_t(1), found.second);
        }
   };
}