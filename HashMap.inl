#include "HashMap.h"

namespace FieaGameEngine
{
#pragma region HashMap

	//constructor
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline FieaGameEngine::HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::HashMap(size_t size)
	{
		if (size == 0)
		{
			throw std::runtime_error("Size cannot be zero");
		}

		m_Buckets.Reserve(size);

		for (size_t i = 0; i < m_Buckets.Capacity(); ++i)
		{
			m_Buckets.PushBack(std::move(ChainType()));
		}
	}

	//operator[]
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline TValue& HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::operator[](const TKey& key)
	{
		auto [it, inserted] = Insert(std::make_pair(key, TValue()));
		return it->second;
	}

	//at
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline TValue& HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::At(const TKey& key)
	{
		Iterator it = Find(key);

		if (it == end())
		{
			throw std::runtime_error("Key not in hash.");
		}

		return it->second;
	}

	//const at
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline const TValue& HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::At(const TKey& key) const
	{
		ConstIterator it = Find(key);

		if (it == end())
		{
			throw std::runtime_error("Key not in hash.");
		}

		return it->second;
	}

	//insert
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline std::pair<typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Iterator, bool>
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Insert(const PairType& pair)
	{
		bool wasInserted = false;
		size_t index = HashKey(pair.first);
		ChainType& chain = m_Buckets[index];
		Iterator it(*this, index, chain.begin());

		if (!chain.IsEmpty())
		{
			SearchChain(it, pair.first);
		}

		if (it.m_ChainIt == chain.end())
		{
			it.m_ChainIt = chain.PushBack(pair);
			++m_Size;
			wasInserted = true;
		}

		return std::make_pair(it, wasInserted);
	}

	//move insert
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline std::pair<typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Iterator, bool>
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Insert(PairType&& pair)
	{
		bool wasInserted = false;
		size_t index = HashKey(pair.first);
		ChainType& chain = m_Buckets[index];
		Iterator it(*this, index, chain.begin());

		if (!chain.IsEmpty())
		{
			SearchChain(it, pair.first);
		}

		if (it.m_ChainIt == chain.end())
		{
			it.m_ChainIt = chain.PushBack(std::move(pair));
			++m_Size;
			wasInserted = true;
		}

		return std::make_pair(it, wasInserted);
	}
	
	//find
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Iterator 
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Find(const TKey& key)
	{
		size_t index = HashKey(key);
		ChainType& chain = m_Buckets[index];
		Iterator it(*this, index, chain.begin());

		SearchChain(it, key);

		if (it.m_ChainIt == chain.end())
		{
			it = end();
		}

		return it;
	}

	//const find
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ConstIterator
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Find(const TKey& key) const
	{
		size_t index = HashKey(key);
		const ChainType& chain = m_Buckets[index];
		ConstIterator it(*this, index, chain.begin());

		SearchChain(it, key);

		if (it.m_ChainIt == chain.end())
		{
			it = end();
		}

		return it;
	}

	//remove
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline void HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Remove(const TKey& key)
	{
		Iterator it = Find(key);
		if (it != end())
		{
			m_Buckets[it.m_Index].Remove(it.m_ChainIt);
			--m_Size;
		}
	}

	//size
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline size_t HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Size()
	{
		return m_Size;
	}

	//containsKey
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline bool HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ContainsKey(TKey& key) const
	{
		return !(Find(key) == end());
	}

	//begin
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Iterator 
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::begin()
	{
		Iterator it;
		if (m_Size == 0 || m_Buckets.Size() == 0)
		{
			it = end();
		}
		else
		{
			size_t index = 0;
			if (m_Buckets[0].IsEmpty())
			{
				index = FindNext(0);
			}

			it = Iterator(*this, index, m_Buckets[index].begin());
		}
		return it;
	}

	//end
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Iterator 
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::end()
	{
		ChainIteratorType temp;
		return Iterator(*this, m_Buckets.Size(), temp);
	}

	//const begin
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ConstIterator
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::begin() const
	{
		ConstIterator it;
		if (m_Size == 0)
		{
			it = end();
		}
		else
		{
			size_t index = 0;
			if (m_Buckets[0].IsEmpty())
			{
				index = FindNext(0);
			}

			it = ConstIterator(*this, index, m_Buckets[index].cbegin());
		}
		return it;
	}

	//const end
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ConstIterator
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::end() const
	{
		ConstChainIteratorType temp;
		return ConstIterator(*this, m_Buckets.Size(), temp);
	}

	//cbegin
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ConstIterator
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::cbegin() const
	{
		ConstIterator it;
		if (m_Size == 0)
		{
			it = cend();
		}
		else
		{
			size_t index = 0;
			if (m_Buckets[0].IsEmpty())
			{
				index = FindNext(0);
			}

			it = ConstIterator(*this, index, m_Buckets[index].cbegin());
		}
		return it;
	}

	//cend
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ConstIterator
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::cend() const
	{
		ConstChainIteratorType temp;
		return ConstIterator(*this, m_Buckets.Size(), temp);
	}

	//clear
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline void HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Clear()
	{
		Iterator it = begin();
		while (it.m_Index != m_Buckets.Size())
		{
			m_Buckets[it.m_Index].Clear();
			it.m_Index = FindNext(it.m_Index);
		}

		m_Size = 0;
	}

	//findNext
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline size_t HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::FindNext(size_t index) const
	{
		while (index != m_Buckets.Size())
		{
			if (index != m_Buckets.Size() - 1)
			{
				++index;

				if (!m_Buckets[index].IsEmpty())
				{
					break;
				}
			}
			else
			{
				++index;
			}
		}

		return index;
	}

	//hashKey
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline size_t HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::HashKey(const TKey& key) const
	{
		HashFunctor hash;
		size_t index = hash(key) % m_Buckets.Size();
		return index;
	}

	//searchChain
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Iterator 
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::SearchChain(Iterator& it, const TKey& toFind)
	{
		for (it; it.m_ChainIt != m_Buckets[it.m_Index].end(); ++it.m_ChainIt)
		{
			if (m_EqualityFunctor(toFind, (*it).first))
			{
				break;
			}
		}

		return it;
	}

	//const searchChain
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ConstIterator
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::SearchChain(ConstIterator& it, const TKey& toFind) const
	{
		for (it; it.m_ChainIt != m_Buckets[it.m_Index].end(); ++it.m_ChainIt)
		{
			if (m_EqualityFunctor(toFind, (*it).first))
			{
				break;
			}
		}

		return it;
	}

#pragma endregion HashMap
	

#pragma region Iterator

	//iterator constructor
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Iterator::Iterator(HashMap& owner, size_t index, ChainIteratorType chain) :
		m_Owner(&owner), m_Index(index), m_ChainIt(chain) { }

	//operator==
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline bool HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Iterator::operator==(const Iterator& other) const
	{
		return !(operator!=(other));
	}

	//operator!=
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline bool HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Iterator::operator!=(const Iterator& other) const
	{
		return m_Owner != other.m_Owner || m_Index != other.m_Index || m_ChainIt != other.m_ChainIt;
	}

	//operator++
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Iterator&
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Iterator::operator++()
	{
		if (m_Owner == nullptr)
		{
			throw std::runtime_error("Unassociated iterator");
		}
		++m_ChainIt;

		if (m_ChainIt == m_Owner->m_Buckets[m_Index].end())
		{
			m_Index = m_Owner->FindNext(m_Index);

			if (m_Index == m_Owner->m_Buckets.Size())
			{
				ChainIteratorType temp;
				m_ChainIt = std::move(temp);
			}
			else
			{
				m_ChainIt = m_Owner->m_Buckets[m_Index].begin();
			}
		}

		return *this;
	}

	//postfix operator++
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Iterator
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Iterator::operator++(int)
	{
		Iterator temp = *this;
		operator++();
		return temp;
	}

	//operator*
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::PairType&
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Iterator::operator*() const
	{
		if (m_Owner == nullptr)
		{
			throw std::runtime_error("Unassociated Iterator");
		}

		return *m_ChainIt;
	}

	//operator->
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::PairType*
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::Iterator::operator->() const
	{
		return &(operator*());
	}

#pragma endregion Iterator

#pragma region ConstIterator

	//constiterator constructor
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ConstIterator::ConstIterator(const HashMap& owner, size_t index, ConstChainIteratorType chain) :
		m_Owner(&owner), m_Index(index), m_ChainIt(chain) { }

	//constiterator from other iterator
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ConstIterator::ConstIterator(Iterator& other) :
		m_Owner(other.m_Owner), m_Index(other.m_Index), m_ChainIt(other.m_ChainIt) { }

	//operator==
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline bool HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return !(operator!=(other));
	}

	//operator!=
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline bool HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return m_Owner != other.m_Owner || m_Index != other.m_Index || m_ChainIt != other.m_ChainIt;
	}

	//operator++
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ConstIterator&
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ConstIterator::operator++()
	{
		if (m_Owner == nullptr)
		{
			throw std::runtime_error("Unassociated ConstIterator");
		}
		++m_ChainIt;

		if (m_ChainIt == m_Owner->m_Buckets[m_Index].end())
		{
			m_Index = m_Owner->FindNext(m_Index);

			if (m_Index == m_Owner->m_Buckets.Size())
			{
				ConstChainIteratorType temp;
				m_ChainIt = std::move(temp);
			}
			else
			{
				m_ChainIt = m_Owner->m_Buckets[m_Index].begin();
			}
		}

		return *this;
	}

	//postfix operator++
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ConstIterator
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ConstIterator::operator++(int)
	{
		ConstIterator temp = *this;
		operator++();
		return temp;
	}

	//operator*
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline const typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::PairType&
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ConstIterator::operator*() const
	{
		if (m_Owner == nullptr)
		{
			throw std::runtime_error("Unassociated ConstIterator");
		}

		return *m_ChainIt;
	}

	//operator->
	template<typename TKey, typename TValue, typename HashFunctor, typename EqualityFunctor>
	inline const typename HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::PairType*
		HashMap<TKey, TValue, HashFunctor, EqualityFunctor>::ConstIterator::operator->() const
	{
		return &(operator*());
	}

#pragma endregion ConstIterator
}
