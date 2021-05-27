#pragma once

namespace FieaGameEngine
{
	template<typename TKey>
	struct DefaultHash final
	{
		size_t operator()(const TKey& key) const;
	};

}

#include "DefaultHash.inl"