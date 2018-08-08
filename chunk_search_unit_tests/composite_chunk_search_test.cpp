#include "stdafx.h"
#include "CppUnitTest.h"

#include "../chunk_search/composite_chunk_search.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace composite_chunk_search_unit_tests
{
	TEST_CLASS(CompositeChunkSearch)
	{
	public:
		TEST_METHOD(ReturnsMatchLengthWhenOnePatternIsIdenticalToHaystack)
		{
			composite_chunk_search<> cs{ "abc", "bcd" };

			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.match_length);
		}

		TEST_METHOD(ReturnsMatchLength0WhenNoneOfPatternsIsFoundInHaystack)
		{
			composite_chunk_search<std::string> cs{ "abc", "bcd", "cde" };

			std::string haystack{ "cbc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(0), found.match_length);
		}

		TEST_METHOD(ReturnsMatchLengthWhenOneOfPatternsIsPartOfHaystack)
		{
			composite_chunk_search<std::string> cs{ "abc", "bcd", "cde" };

			std::string haystack{ "bcabcde" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.match_length);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundWhenOneOfPatternsIsPartOfHaystack)
		{
			composite_chunk_search<std::string> cs{ "abc", "bcd", "cde" };

			std::string haystack{ "bcabcde" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(5), long(std::distance(haystack.cbegin(), found.end)));
		}

		TEST_METHOD(ReturnsMatchLengthOfFoundWhenOneOfPatternsIsPartOfHaystack)
		{
			composite_chunk_search<std::string> cs{ "abc", "bcag", "bcde", "cac" };

			std::string haystack{ "bcabcde" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.match_length);
			Assert::AreEqual(long(5), long(std::distance(haystack.cbegin(), found.end)));
		}

		TEST_METHOD(ReturnsMatchLengthOfFirstPatternMatchedEntirelyWhenAllPatternsArePartOfHaystack)
		{
			composite_chunk_search<std::string> cs{ "abcde", "abcd", "bcd", "bcde" };

			std::string haystack{ "aaabcdef" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(4), found.match_length);
			Assert::AreEqual(long(6), long(std::distance(haystack.cbegin(), found.end)));
		}

		TEST_METHOD(ReturnsMatchLengthOfLongestPatternForPatternsThatHaveSameEnd)
		{
			composite_chunk_search<std::string> cs{ "aaabcd", "aabcd", "abcd" };

			std::string haystack{ "aaaabcdef" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(6), found.match_length);
			Assert::AreEqual(long(7), long(std::distance(haystack.cbegin(), found.end)));
		}

		TEST_METHOD(ReturnsMatchLengthOfLongestPatternForPatternsThatHaveSameEndWhenPatternsAreSplitIn2Haystacks)
		{
			composite_chunk_search<std::string> cs{ "aaabcd", "aabcd", "abcd" };

			std::string haystack{ "aa" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			haystack = "abcdef";
			found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(6), found.match_length);
			Assert::AreEqual(long(4), long(std::distance(haystack.cbegin(), found.end)));
		}

		TEST_METHOD(ReturnsMatchLengthWhenTheOnlyPatternIsIdenticalToHaystack)
		{
			composite_chunk_search<std::string> cs{ "abc" };

			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.match_length);
		}

		TEST_METHOD(ReturnsMatchLength0WhenTheOnlyPatternsIsFoundInHaystack)
		{
			composite_chunk_search<std::string> cs{ "abc" };

			std::string haystack{ "cbc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(0), found.match_length);
		}

		TEST_METHOD(ReturnsResultWhenPatternsAreProvidedAsCollectionToConstructor)
		{
			std::string patterns[] = { "abc", "bcd" };
			composite_chunk_search<std::string> cs(patterns);

			std::string haystack{ " abcd" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.match_length);
			Assert::AreEqual(long(4), long(std::distance(haystack.cbegin(), found.end)));
		}

		TEST_METHOD(ReturnsResultWhenPatternIsAddedSubsequently)
		{
			composite_chunk_search<std::string> ccs({ "bcd" });

			std::string haystack1{ " abce" };
			auto found = ccs.search(haystack1.cbegin(), haystack1.cend());

			Assert::AreEqual(size_t(0), found.match_length);

			ccs.add_pattern("abcd");

			std::string haystack2{ "dabcda" };
			found = ccs.search(haystack2.cbegin(), haystack2.cend());

			Assert::AreEqual(size_t(4), found.match_length);
			Assert::AreEqual(long(5), long(std::distance(haystack2.cbegin(), found.end)));
		}
	};
}
