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

template <typename T = std::string>
class composite_chunk_search
{
	using ChunkSearch = chunk_search<T>;
public:
	composite_chunk_search() = default;

	template <typename C>
	composite_chunk_search(C& patterns)
	{
		for (const auto& pattern : patterns)
			patterns_m.emplace_back(pattern);
	}

	template <typename C>
	composite_chunk_search(C&& patterns) = delete;

	void add_pattern(typename T::const_iterator pattern_first, typename T::const_iterator pattern_last)
	{
		patterns_m.emplace_back(pattern_first, pattern_last);
	}

	void add_pattern(T& pattern)
	{
		patterns_m.emplace_back(pattern);
	}

	// prevent passing temporary objects
	void add_pattern(T&& pattern) = delete;

	template <typename ForwardIterator>
	std::pair<size_t, ForwardIterator> search(ForwardIterator haystack_first, ForwardIterator haystack_last)
	{
		std::vector<std::pair<size_t, ForwardIterator>> successful;
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
