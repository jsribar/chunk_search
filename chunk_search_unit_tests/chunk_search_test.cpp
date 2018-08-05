#include "stdafx.h"
#include "CppUnitTest.h"

#include "../chunk_search/chunk_search.h"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace chunk_search_unit_tests
{		
	TEST_CLASS(ChunkSearch)
	{
	public:
		TEST_METHOD(ReturnsMatchLengthEqualToPatternLenghtWhenPatternIsIdenticalToHaystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.first);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundWhenPatternIsIdenticalToHaystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(3), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(ReturnsIteratorToEndOfHaystackWhenPatternIsIdenticalToHaystack)
		{
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "abc" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(found.second == haystack.cend());
		}

		TEST_METHOD(ReturnsMatchLengthWhenPatternIsPartOfHaystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "01abc23" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.first);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundWhenPatternIsPartOfHaystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "01abc23" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(5), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(ReturnsMatchLengthWhenPatternIsPartOfHaystackPrecedeedWithPartialMatch)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "ababc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.first);
		}
		
		TEST_METHOD(ReturnsIteratorToEndOfFoundWhenPatternIsPartOfHaystackPrecedeedWithPartialMatch)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "ababc" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(5), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(ReturnsMatchLength0IfPatternIsNotFound)
		{
			std::string pattern{ "abd" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(0), found.first);
		}

		TEST_METHOD(ReturnsIteratorToHaystackEndIfPatternIsNotFound)
        {
            std::string pattern{ "abd" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "abc" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(found.second == haystack.cend());
		}

		TEST_METHOD(ReturnsMatchLength0IfOnlyPartOfPatternIsFound)
		{
			std::string pattern{ "012ab" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "012" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(0), found.first);
		}

		TEST_METHOD(ReturnsIteratorToHaystackEndIfOnlyPartOfPatternIsFound)
        {
            std::string pattern{ "012ab" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "012" };
            auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(found.second == haystack.cend());
		}

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPatternIsPartOfSecondHaystack)
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

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterSecondCallWhenPatternIsPartOfSecondHaystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "0123" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "012abcd";
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(6), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPartOfPatternIsInFirstHaystackButPatternIsPartOfSecondHaystack)
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

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterSecondCallWhenPartOfPatternIsInFirstHaystackButPatternIsPartOfSecondHaystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "ab" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "abcd";
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(3), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPatternIsSplitBetweenFirstAndSecondHaystacks)
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

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterSecondCallWhenPatternIsSplitBetweenFirstAndSecondHaystacks)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "a" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			haystack = "bc";
			found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(2), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPartialPatternIsSplitBetweenFirstAndSecondHaystacksButIsInSecondHaystack)
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

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterSecondCallWhenPartialPatternIsSplitBetweenFirstAndSecondHaystacksButIsInSecondHaystack)
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

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPatternIsInSecondHaystack)
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
		
		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPatternIsInSecondHaystackButNoMatchInFirstHaystack)
        {
            std::string pattern{ "abc" };
            chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "def" };
            cs.search(haystack.cbegin(), haystack.cend());

            haystack = "abc";
            auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.first);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterSecondCallWhenPatternIsInSecondHaystackButNoMatchInFirstHaystack)
		{
			std::string pattern{ "abc" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "def" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "abc";
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(found.second == haystack.cend());
		}

		TEST_METHOD(ReturnsMatchLengthAfterThirdCallWhenPatternIsSplitBetweenThreeHaystacks)
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

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterThirdCallWhenPatternIsSplitBetweenThreeHaystacks)
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

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenRepetitivePatternIsSplitBetweenTwoHaystacks)
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

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterSecondCallWhenRepetitivePatternIsSplitBetweenTwoHaystacks)
		{
			std::string pattern{ "abac" };
			chunk_search<std::string::const_iterator> cs{ pattern.cbegin(), pattern.cend() };

			std::string haystack{ "aba" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "bac";
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(3), long(std::distance(haystack.cbegin(), found.second)));
		}

		TEST_METHOD(ReturnsMatchLengthAfterThirdCallWhenrepetitivePatternIsSplitBetweenThreeHaystacks)
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

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterThirdCallWhenRepetitivePatternIsSplitBetweenThreeHaystacks)
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

		TEST_METHOD(ReturnsMatchLengthAfterThirdCallWhenRepetitivePatternIsSplitBetweenTwoHaystacks)
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

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterThirdCallWhenRepetitivePatternIsSplitBetweenTwoHaystacks)
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
