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

	composite_chunk_search(std::initializer_list<T> patterns)
	{
		for (const auto& pattern : patterns)
			searches_m.emplace_back(std::move(pattern));
	}

	template <typename C>
	composite_chunk_search(const C& patterns)
	{
		for (const auto& pattern : patterns)
			searches_m.emplace_back(pattern);
	}

	template <typename C>
	composite_chunk_search(C&& patterns)
	{
		for (const auto& pattern : patterns)
			searches_m.emplace_back(std::move(pattern));
	}

	composite_chunk_search& operator=(composite_chunk_search<T>&& search)
	{
		searches_m.clear();
		for (auto& pattern : search.searches_m)
			searches_m.push_back(std::move(pattern));
		return *this;
	}

	// disable copying
	composite_chunk_search(const composite_chunk_search&) = delete;
	composite_chunk_search& operator=(const composite_chunk_search<T>&) = delete;

	void add_pattern(const T& pattern)
	{
		searches_m.emplace_back(pattern);
	}

	void add_pattern(T&& pattern)
	{
		searches_m.emplace_back(std::move(pattern));
	}

	template <typename ForwardIterator>
	chunk_search_result<ForwardIterator> search(ForwardIterator haystack_first, ForwardIterator haystack_last)
	{
		std::vector<chunk_search_result<ForwardIterator>> successful;
		for (auto& search : searches_m)
		{
			auto result = search.search(haystack_first, haystack_last);
			if (result.match_length > 0)
				successful.push_back(result);
		}
		if (successful.empty())
            return chunk_search_result<ForwardIterator>{ 0, haystack_last };
		// return match that ends foremost and if two end at the same position, return the shorter one
		return *std::min_element(successful.begin(), successful.end(), [&haystack_first](const auto& res1, const auto& res2)
		{
			return res1.end - res2.end ? res1.end < res2.end : res1.match_length > res2.match_length;
		});
	}

private:
	std::vector<ChunkSearch> searches_m;
};
