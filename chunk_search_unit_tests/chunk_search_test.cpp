#include "stdafx.h"
#include "CppUnitTest.h"

#include "../chunk_search/chunk_search.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace chunk_search_unit_tests
{
	TEST_CLASS(ChunkSearch)
	{
	public:
		TEST_METHOD(ReturnsMatchLengthEqualToPatternLenghtWhenPatternIsIdenticalToHaystack)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.match_length);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundWhenPatternIsIdenticalToHaystack)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(3), long(std::distance(haystack.cbegin(), found.end)));
		}

		TEST_METHOD(ReturnsIteratorToEndOfHaystackWhenPatternIsIdenticalToHaystack)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(found.end == haystack.cend());
		}

		TEST_METHOD(ReturnsMatchLengthWhenPatternIsPartOfHaystack)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "01abc23" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.match_length);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundWhenPatternIsPartOfHaystack)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "01abc23" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(5), long(std::distance(haystack.cbegin(), found.end)));
		}

		TEST_METHOD(ReturnsMatchLengthWhenPatternIsPartOfHaystackPrecedeedWithPartialMatch)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "ababc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.match_length);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundWhenPatternIsPartOfHaystackPrecedeedWithPartialMatch)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "ababc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(5), long(std::distance(haystack.cbegin(), found.end)));
		}

		TEST_METHOD(ReturnsMatchLength0IfPatternIsNotFound)
		{
			chunk_search<> cs{ "abd" };

			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(0), found.match_length);
		}

		TEST_METHOD(ReturnsIteratorToHaystackEndIfPatternIsNotFound)
		{
			chunk_search<> cs{ "abd" };

			std::string haystack{ "abc" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(found.end == haystack.cend());
		}

		TEST_METHOD(ReturnsMatchLength0IfOnlyPartOfPatternIsFound)
		{
			chunk_search<> cs{ "012ab" };

			std::string haystack{ "012" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(0), found.match_length);
		}

		TEST_METHOD(ReturnsIteratorToHaystackEndIfOnlyPartOfPatternIsFound)
		{
			chunk_search<> cs{ "012ab" };

			std::string haystack{ "012" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(found.end == haystack.cend());
		}

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPatternIsPartOfSecondHaystack)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "0123" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsFalse(found.match_length);

			haystack = "012abcd";
			found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.match_length);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterSecondCallWhenPatternIsPartOfSecondHaystack)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "0123" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "012abcd";
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(6), long(std::distance(haystack.cbegin(), found.end)));
		}

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPartOfPatternIsInFirstHaystackButPatternIsPartOfSecondHaystack)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "ab" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsFalse(found.match_length);

			haystack = "abcd";
			found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.match_length);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterSecondCallWhenPartOfPatternIsInFirstHaystackButPatternIsPartOfSecondHaystack)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "ab" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "abcd";
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(3), long(std::distance(haystack.cbegin(), found.end)));
		}

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPatternIsSplitBetweenFirstAndSecondHaystacks)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "a" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsFalse(found.match_length);

			haystack = "bc";
			found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.match_length);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterSecondCallWhenPatternIsSplitBetweenFirstAndSecondHaystacks)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "a" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			haystack = "bc";
			found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(2), long(std::distance(haystack.cbegin(), found.end)));
		}

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPartialPatternIsSplitBetweenFirstAndSecondHaystacksButIsInSecondHaystack)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "a" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsFalse(found.match_length);

			haystack = "bdabcd";
			found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.match_length);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterSecondCallWhenPartialPatternIsSplitBetweenFirstAndSecondHaystacksButIsInSecondHaystack)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "a" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(found.end == haystack.cend());

			haystack = "bdabcd";
			found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(5), long(std::distance(haystack.cbegin(), found.end)));
		}

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPatternIsInSecondHaystack)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "ab" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(0), found.match_length);

			haystack = "abc";
			found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.match_length);
		}

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPatternIsInSecondHaystackButNoMatchInFirstHaystack)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "def" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "abc";
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.match_length);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterSecondCallWhenPatternIsInSecondHaystackButNoMatchInFirstHaystack)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "def" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "abc";
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(found.end == haystack.cend());
		}

		TEST_METHOD(ReturnsMatchLengthAfterThirdCallWhenPatternIsSplitBetweenThreeHaystacks)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "da" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "b";
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsFalse(found.match_length);

			haystack = "c";
			found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(3), found.match_length);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterThirdCallWhenPatternIsSplitBetweenThreeHaystacks)
		{
			chunk_search<> cs{ "abc" };

			std::string haystack{ "da" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "b";
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "c";
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(found.end == haystack.cend());
		}

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenRepetitivePatternIsSplitBetweenTwoHaystacks)
		{
			chunk_search<> cs{ "abac" };

			std::string haystack{ "aba" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsFalse(found.match_length);

			haystack = "bac";
			found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(4), found.match_length);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterSecondCallWhenRepetitivePatternIsSplitBetweenTwoHaystacks)
		{
			chunk_search<> cs{ "abac" };

			std::string haystack{ "aba" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "bac";
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(3), long(std::distance(haystack.cbegin(), found.end)));
		}

		TEST_METHOD(ReturnsMatchLengthAfterThirdCallWhenrepetitivePatternIsSplitBetweenThreeHaystacks)
		{
			chunk_search<> cs{ "abababc" };

			std::string haystack{ "aba" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsFalse(found.match_length);

			haystack = "bab";
			found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsFalse(found.match_length);

			haystack = "abcd";
			found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(7), found.match_length);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterThirdCallWhenRepetitivePatternIsSplitBetweenThreeHaystacks)
		{
			chunk_search<> cs{ "abababc" };

			std::string haystack{ "aba" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "bab";
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "abcd";
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(3), long(std::distance(haystack.cbegin(), found.end)));
		}

		TEST_METHOD(ReturnsMatchLengthAfterThirdCallWhenRepetitivePatternIsSplitBetweenTwoHaystacks)
		{
			chunk_search<> cs{ "baba" };

			std::string haystack{ "aba" };
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsFalse(found.match_length);

			haystack = "bbab";
			found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::IsFalse(found.match_length);

			haystack = "abcd";
			found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(size_t(4), found.match_length);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterThirdCallWhenRepetitivePatternIsSplitBetweenTwoHaystacks)
		{
			chunk_search<> cs{ "baba" };

			std::string haystack{ "aba" };
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "bbab";
			cs.search(haystack.cbegin(), haystack.cend());

			haystack = "abcd";
			auto found = cs.search(haystack.cbegin(), haystack.cend());

			Assert::AreEqual(long(1), long(std::distance(haystack.cbegin(), found.end)));
		}
	};
}
