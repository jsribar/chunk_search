/*
	Copyright(c) 2018 Julijan Sribar julijan(dot)sribar(at)gmail(dot)com

	This software is provided 'as-is', without any express or implied
	warranty.In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions :

	1. The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software.If you use this software
	in a product, an acknowledgment in the product documentation would be
	appreciated but is not required.
	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
*/

#pragma once

#include "chunk_search.h"

#include <algorithm>
#include <utility>
#include <vector>

template <typename ForwardIterator1>
class composite_chunk_search
{
	using ChunkSearch = chunk_search<ForwardIterator1>;
public:
	composite_chunk_search() = default;

	void add_pattern(ForwardIterator1 pattern_first, ForwardIterator1 pattern_last)
	{
		patterns_m.emplace_back(pattern_first, pattern_last);
	}

	template <typename T>
	void add_pattern(T& pattern)
	{
		patterns_m.emplace_back(pattern);
	}

	// prevent passing temporary objects
	template <typename T>
	void add_pattern(T&& pattern) = delete;

	template <typename ForwardIterator2>
	std::pair<size_t, ForwardIterator2> search(ForwardIterator2 haystack_first, ForwardIterator2 haystack_last)
	{
		std::vector<std::pair<size_t, ForwardIterator2>> successful;
		for (auto& pattern : patterns_m)
		{
			auto result = pattern.search(haystack_first, haystack_last);
			if (result.first > 0)
				successful.push_back(result);
		}
		if (successful.empty())
			return std::make_pair(0, haystack_last);
		// return match that ends foremost and if two end at the same position, return the shorter one
		return *std::min_element(successful.begin(), successful.end(), [&haystack_first](const auto& res1, const auto& res2) 
		{ 
			return res1.second - res2.second ? res1.second < res2.second : res1.first > res2.first;
		});
	}

private:
	std::vector<ChunkSearch> patterns_m;
};
