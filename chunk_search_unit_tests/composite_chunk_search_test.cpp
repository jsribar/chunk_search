#include "stdafx.h"
#include "CppUnitTest.h"

#include "../chunk_search/composite_chunk_search.h"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace composite_chunk_search_unit_tests
{
	TEST_CLASS(CompositeChunkSearch)
	{
	public:
		TEST_METHOD(ReturnsMatchLengthWhenOnePatternIsIdenticalToHaystack)
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

		TEST_METHOD(ReturnsMatchLength0WhenNoneOfPatternsIsFoundInHaystack)
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

		TEST_METHOD(ReturnsMatchLengthWhenOneOfPatternsIsPartOfHaystack)
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

		TEST_METHOD(ReturnsIteratorToEndOfFoundWhenOneOfPatternsIsPartOfHaystack)
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

		TEST_METHOD(ReturnsMatchLengthOfFoundWhenOneOfPatternsIsPartOfHaystack)
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

		TEST_METHOD(ReturnsMatchLengthOfFirstPatternMatchedEntirelyWhenAllPatternsArePartOfHaystack)
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

		TEST_METHOD(ReturnsMatchLengthOfLongestPatternForPatternsThatHaveSameEnd)
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

		TEST_METHOD(ReturnsMatchLengthOfLongestPatternForPatternsThatHaveSameEndWhenPatternsAreSplitIn2Haystacks)
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

		TEST_METHOD(ReturnsMatchLengthWhenTheOnlyPatternIsIdenticalToHaystack)
		{
			composite_chunk_search<std::string::const_iterator> cs;
			std::string pattern{ "abc" };
			cs.add_pattern(pattern);

			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.first);
		}

		TEST_METHOD(ReturnsMatchLength0WhenTheOnlyPatternsIsFoundInHaystack)
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
