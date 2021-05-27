#include "DefaultHash.h"
#include <cstdint>
#include <string.h>
#include <string>

namespace FieaGameEngine
{
	const size_t HashPrime = 31;

	inline size_t AdditiveHash(const std::uint8_t* key, size_t size)
	{
		size_t hash = 0;

		for (size_t i = 0; i < size; ++i)
		{
			hash += HashPrime * key[i];
		}

		return hash;
	}

	template<typename TKey>
	inline size_t DefaultHash<TKey>::operator()(const TKey& key) const
	{
		const std::uint8_t* data = reinterpret_cast<const std::uint8_t*>(&key);

		return AdditiveHash(data, sizeof(TKey));
	}

	template<>
	struct DefaultHash<char*>
	{
		inline size_t operator()(const char* key) const
		{
			const std::uint8_t* data = reinterpret_cast<const std::uint8_t*>(key);
			
			return AdditiveHash(data, sizeof(*key));
		}
	};

	template<>
	struct DefaultHash<const char*>
	{
		inline size_t operator()(const char* key) const
		{
			const std::uint8_t* data = reinterpret_cast<const std::uint8_t*>(key);

			return AdditiveHash(data, strlen(key));
		}
	};

	template<>
	struct DefaultHash<const char* const>
	{
		inline size_t operator()(const char* const key) const
		{
			const std::uint8_t* data = reinterpret_cast<const std::uint8_t*>(key);

			return AdditiveHash(data, strlen(key));
		}
	};

	template<>
	struct DefaultHash<char* const>
	{
		inline size_t operator()(char* const key) const
		{
			const std::uint8_t* data = reinterpret_cast<const std::uint8_t*>(key);

			return AdditiveHash(data, sizeof(*key));
		}
	};

	template<>
	struct DefaultHash<std::string>
	{
		inline size_t operator()(const std::string& key) const
		{
			const std::uint8_t* data = reinterpret_cast<const std::uint8_t*>(key.c_str());

			return AdditiveHash(data, key.length());
		}
	};

	template<>
	struct DefaultHash<const std::string>
	{
		inline size_t operator()(const std::string& key) const
		{
			const std::uint8_t* data = reinterpret_cast<const std::uint8_t*>(key.c_str());

			return AdditiveHash(data, key.length());
		}
	};

	template<>
	struct DefaultHash<int>
	{
		inline size_t operator()(int key) const
		{
			return static_cast<size_t>(key);
		}
	};
}
