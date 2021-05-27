#pragma once
#include "DefaultEquality.h"
#include "DefaultHash.h"
#include "Vector.h"
#include "SList.h"
#include <utility>

namespace FieaGameEngine
{
	/// <summary>
	/// HashMap class
	/// stores key-value pairs and can retrieve them in constant time (best case)
	/// </summary>
	/// <typeparam name="TKey">the data type for the keys</typeparam>
	/// <typeparam name="TValue">the data type for the values</typeparam>
	/// <typeparam name="HashFunctor">the functor to be used for hashing the keys</typeparam>
	/// <typeparam name="EqualityFunctor">the functor to be used determining equality</typeparam>
	template <typename TKey, typename TValue, typename HashFunctor = DefaultHash<TKey>, typename EqualityFunctor = DefaultEquality<TKey>>
	class HashMap
	{
		friend class Iterator;
		friend class ConstIterator;

	public:
		using PairType = std::pair<const TKey, TValue>;

	private:
		using ChainType = SList<PairType>;
		using BucketType = Vector<ChainType>;

		using ChainIteratorType = typename ChainType::Iterator;
		using ConstChainIteratorType = typename ChainType::ConstIterator;

	public:

		/// <summary>
		/// iterator class for hashmap
		/// allows for an outside user to iterate forward through the map
		/// </summary>
		class Iterator final
		{
			friend HashMap;
			friend class ConstIterator;

		public:
			/// <summary>
			/// default constructor for Iterator
			/// </summary>
			Iterator() = default;
			
			/// <summary>
			/// default copy constructor for Iterator
			/// </summary>
			/// <param name="ToCopy">the iterator to be copied</param>
			Iterator(const Iterator & ToCopy) = default;
			
			/// <summary>
			/// default move constructor for Iterator
			/// </summary>
			/// <param name="ToMove">the iterator to be moved</param>
			/// <returns>the iterator in its new location</returns>
			Iterator(Iterator && ToMove) noexcept = default;
			
			/// <summary>
			/// default copy assignment operator for Iterator
			/// </summary>
			/// <param name="ToCopy">the iterator to be copied</param>
			/// <returns>the freshly copied iterator</returns>
			Iterator& operator=(const Iterator & ToCopy) = default;
			
			/// <summary>
			/// default move assignment operator for Iterator
			/// </summary>
			/// <param name="ToMove">the iterator to be moved</param>
			/// <returns>teh iterator in its new location</returns>
			Iterator& operator=(Iterator && ToMove) noexcept = default;
			
			/// <summary>
			/// default destructor for Iterator
			/// </summary>
			~Iterator() = default;
			
			/// <summary>
			/// == operator for Iterator
			/// </summary>
			/// <param name="other">the iterator being compared</param>
			/// <returns>whether or not the iterators being compared are equal</returns>
			bool operator==(const Iterator & other) const;
			
			/// <summary>
			/// not equal operator for Iterator
			/// </summary>
			/// <param name="other">the iterator being compared</param>
			/// <returns>whether or not the iterators being compared are not equal</returns>
			bool operator!=(const Iterator & other) const;
			
			/// <summary>
			/// prefix incrementor for iterator
			/// moves the iterator to the next node
			/// </summary>
			/// <returns>the iterator in its new location</returns>
			/// /// <exception cref="std::runtime_error">throws an exception if the iterator has no owner</exception>
			Iterator& operator++();
			
			/// <summary>
			/// postfix incrementor for iterator
			/// moves the iterator to the next node
			/// </summary>
			/// <returns>the iterator in its new location</returns>
			Iterator operator++(int);
			
			/// <summary>
			/// dereference operator for iterator
			/// </summary>
			/// <returns>the value of the pair being pointed to</returns>
			/// <exception cref="std::runtime_error">throws exception if attempting to dereference a nullptr</exception>
			PairType& operator*() const;

			/// <summary>
			/// pointer dereference operator for iterator
			/// </summary>
			/// <returns>a pointer to the pair the iterator is looking at</returns>
			PairType* operator->() const;

		private:
			/// <summary>
			/// special iterator constructor that takes a node to point to, and sets the owner
			/// </summary>
			/// <param name="owner">the hashmap that owns the iterator</param>
			/// <param name="index">the index the iterator is to point to</param>
			/// <param name="slist">the iterator for the specific bucket</param>
			Iterator(HashMap& owner, size_t index, ChainIteratorType slist);

			/// <summary>
			/// the owner of the iterator
			/// </summary>
			HashMap* m_Owner = nullptr;

			/// <summary>
			/// the index the iterator is pointing to 
			/// </summary>
			size_t m_Index = 0;

			/// <summary>
			/// the current spot in the SList
			/// </summary>
			ChainIteratorType m_ChainIt;
		};

		/// <summary>
		/// ConstIterator class for hashmap
		/// allows for an outside user to iterate forward through a const map
		/// </summary>
		class ConstIterator final
		{
			friend class HashMap;

		public:
			/// <summary>
			/// default constructor for Iterator
			/// </summary>
			ConstIterator() = default;

			/// <summary>
			/// constructor that constructs a const iterator from a regular iterator
			/// </summary>
			/// <param name="other">the iterator to make a ConstIterator with</param>
			ConstIterator(Iterator& other);

			/// <summary>
			/// default copy constructor for ConstIterator
			/// </summary>
			/// <param name="ToCopy">the ConstIterator to be copied</param>
			ConstIterator(const ConstIterator & ToCopy) = default;

			/// <summary>
			/// default move constructor for ConstIterator
			/// </summary>
			/// <param name="ToMove">the ConstIterator to be moved</param>
			/// <returns>the ConstIterator in its new location</returns>
			ConstIterator(ConstIterator && ToMove) noexcept = default;

			/// <summary>
			/// default copy assignment operator for ConstIterator
			/// </summary>
			/// <param name="ToCopy">the ConstIterator to be copied</param>
			/// <returns>the freshly copied ConstIterator</returns>
			ConstIterator& operator=(const ConstIterator & ToCopy) = default;

			/// <summary>
			/// default move assignment operator for ConstIterator
			/// </summary>
			/// <param name="ToMove">the ConstIterator to be moved</param>
			/// <returns>teh ConstIterator in its new location</returns>
			ConstIterator& operator=(ConstIterator && ToMove) noexcept = default;

			/// <summary>
			/// default destructor for ConstIterator
			/// </summary>
			~ConstIterator() = default;

			/// <summary>
			/// == operator for ConstIterator
			/// </summary>
			/// <param name="other">the ConstIterator being compared</param>
			/// <returns>whether or not the ConstIterators being compared are equal</returns>
			bool operator==(const ConstIterator & other) const;

			/// <summary>
			/// not equal operator for ConstIterator
			/// </summary>
			/// <param name="other">the ConstIterator being compared</param>
			/// <returns>whether or not the ConstIterators being compared are not equal</returns>
			bool operator!=(const ConstIterator & other) const;

			/// <summary>
			/// prefix incrementor for ConstIterator
			/// moves the ConstIterator to the next node
			/// </summary>
			/// <returns>the ConstIterator in its new location</returns>
			/// /// <exception cref="std::runtime_error">throws an exception if the ConstIterator has no owner</exception>
			ConstIterator& operator++();

			/// <summary>
			/// postfix incrementor for ConstIterator
			/// moves the ConstIterator to the next node
			/// </summary>
			/// <returns>the ConstIterator in its new location</returns>
			ConstIterator operator++(int);

			/// <summary>
			/// dereference operator for ConstIterator
			/// </summary>
			/// <returns>the value of the node being pointed to</returns>
			/// <exception cref="std::runtime_error">throws exception if attempting to dereference a nullptr</exception>
			const PairType& operator*() const;

			/// <summary>
			/// pointer dereference operator for ConstIterator
			/// </summary>
			/// <returns>a pointer to the pair the iterator is looking at</returns>
			const PairType* operator->() const;

		private:
			/// <summary>
			/// special ConstIterator constructor that takes a node to point to, and sets the owner
			/// </summary>
			/// <param name="owner">the hashmap that owns the ConstIterator</param>
			/// <param name="index">the index the ConstIterator is to point to</param>
			/// <param name="slist">the ConstIterator for the specific bucket</param>
			ConstIterator(const HashMap& owner, size_t index, ConstChainIteratorType slist);

			/// <summary>
			/// the owner of the ConstIterator
			/// </summary>
			const HashMap* m_Owner = nullptr;

			/// <summary>
			/// the index the ConstIterator is pointing to 
			/// </summary>
			size_t m_Index = 0;

			/// <summary>
			/// the current spot in the SList
			/// </summary>
			ConstChainIteratorType m_ChainIt;
		};

		/// <summary>
		/// constructor for hashmap
		/// </summary>
		/// <param name="size">the number of buckets the hashmap is to have</param>
		HashMap(size_t size = 11);

		/// <summary>
		/// default copy constructor for hashmap
		/// </summary>
		/// <param name="ToCopy">the hashmap to be copied</param>
		HashMap(const HashMap& ToCopy) = default;

		/// <summary>
		/// default move constructor for hashmap
		/// </summary>
		/// <param name="ToMove">the hashmap to be moved</param>
		HashMap(HashMap&& ToMove) = default;

		/// <summary>
		/// default copy assignment operator for hashmap
		/// </summary>
		/// <param name="ToCopy">the hashmap to be copied</param>
		/// <returns>freshly copied hashmap</returns>
		HashMap& operator=(const HashMap& ToCopy) = default;

		/// <summary>
		/// default move constructor for hashmap
		/// </summary>
		/// <param name="ToMove">the hashmao to be moved</param>
		/// <returns>the freshly moved hashmap</returns>
		HashMap& operator=(HashMap&& ToMove) = default;

		/// <summary>
		/// default destructor for hashmap
		/// </summary>
		~HashMap() = default;

		/// <summary>
		/// index operator for hashmap
		/// takes in a key and returns the associated value
		/// if the key was not found, it creates a new pair with a default constructed TValue and returns that
		/// </summary>
		/// <param name="key">the key to be found</param>
		/// <returns>the key value pair associated with the key</returns>
		TValue& operator[](const TKey& key);

		/// <summary>
		/// returns a pair from a certain key value
		/// </summary>
		/// <param name="key">the key to find the pair at</param>
		/// <returns>the given pair</returns>
		/// <exception cref="runtime_error">throws an exception if the key is not in the map</exception>
		TValue& At(const TKey& key);

		/// <summary>
		/// const version of at
		/// returns a pair from a certain key value
		/// </summary>
		/// <param name="key">the key to find the pair at</param>
		/// <returns>the given pair</returns>
		/// <exception cref="runtime_error">throws an exception if the key is not in the map</exception>
		const TValue& At(const TKey& key) const;

		/// <summary>
		/// inserts a pair into the hashmap
		/// hashes the key, ensures that that key is not already in the list, adds it to the appropriate bucket
		/// </summary>
		/// <param name="pair">the pair to be inserted</param>
		/// <returns>an iterator pointing at the added pair</returns>
		std::pair<Iterator, bool> Insert(const PairType& pair);

		/// <summary>
		/// move version of insert
		/// inserts a pair into the hashmap
		/// hashes the key, ensures that that key is not already in the list, adds it to the appropriate bucket
		/// </summary>
		/// <param name="pair">the pair to be inserted</param>
		/// <returns>an iterator pointing at the added pair</returns>
		std::pair<Iterator, bool> Insert(PairType&& pair);

		/// <summary>
		/// Finds the location of a pair based on its key
		/// returns an iterator pointing at said key
		/// </summary>
		/// <param name="key">the key to be found</param>
		/// <returns>an iterator pointing to the pair</returns>
		Iterator Find(const TKey& key);

		/// <summary>
		/// const version of find
		/// Finds the location of a pair based on its key
		/// returns an iterator pointing at said key
		/// </summary>
		/// <param name="key">the key to be found</param>
		/// <returns>a ConstIterator pointing to the pair</returns>
		ConstIterator Find(const TKey& key) const;

		/// <summary>
		/// removes a pair based on its key
		/// does nothing if it does not find the pair
		/// </summary>
		/// <param name="Key">the key of the pair to be removed</param>
		void Remove(const TKey& key);

		/// <summary>
		/// returns the number of pairs in the hashmap
		/// </summary>
		/// <returns>the number of pairs in the hashmap</returns>
		size_t Size();

		/// <summary>
		/// checks whether or not the hashmap contains a key
		/// </summary>
		/// <param name="key">the key to be found</param>
		/// <returns>whether or not the key is in the map</returns>
		bool ContainsKey(TKey& key) const;

		/// <summary>
		/// initializes an iterator at the first populated bucket
		/// </summary>
		/// <returns>the new iterator</returns>
		Iterator begin();

		/// <summary>
		/// initializes an iterator past the end of the map
		/// </summary>
		/// <returns>the new iterator</returns>
		Iterator end();

		/// <summary>
		/// initializes a ConstIterator at the first populated bucket
		/// </summary>
		/// <returns>the new iterator</returns>
		ConstIterator begin() const;

		/// <summary>
		/// initializes a ConstIterator past the end of the map
		/// </summary>
		/// <returns>the new iterator</returns>
		ConstIterator end() const;

		/// <summary>
		/// initializes a ConstIterator at the first populated bucket
		/// </summary>
		/// <returns>the new iterator</returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// initializes a ConstIterator past the end of the map
		/// </summary>
		/// <returns>the new iterator</returns>
		ConstIterator cend() const;

		/// <summary>
		/// clears out the hashmap
		/// </summary>
		void Clear();

		/// <summary>
		/// finds the next 
		/// </summary>
		/// <param name="it"></param>
		/// <returns></returns>
		size_t FindNext(size_t index) const;

		/// <summary>
		/// calls the hash function on the key and mods it by the number of buckets
		/// </summary>
		/// <param name="key">the key to be hashed</param>
		/// <returns>the bucket it goes in</returns>
		size_t HashKey(const TKey& key) const;

	private:
		/// <summary>
		/// searches through one chain for a key
		/// </summary>
		/// <param name="it">the iterator pointing to the chain</param>
		/// <param name="toFind">the key to be found</param>
		/// <returns>the iterator pointing at the found value, or the end of that bucket if it was not found</returns>
		Iterator SearchChain(Iterator& it, const TKey& toFind);

		/// <summary>
		/// const version of searchChain
		/// searches through one chain for a key
		/// </summary>
		/// <param name="it">the iterator pointing to the chain</param>
		/// <param name="toFind">the key to be found</param>
		/// <returns>the ConstIterator pointing at the found value, or the end of that bucket if it was not found</returns>
		ConstIterator SearchChain(ConstIterator& it, const TKey& toFind) const;

		/// <summary>
		/// the vector containing the buckets
		/// </summary>
		BucketType m_Buckets;

		/// <summary>
		/// the equality functor to be used in the hashmap
		/// </summary>
		EqualityFunctor m_EqualityFunctor;

		/// <summary>
		/// the number of pairs in the map
		/// </summary>
		size_t m_Size = 0;
	};
}

#include "HashMap.inl"