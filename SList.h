#pragma once

namespace FieaGameEngine 
{
	/// <summary>
	/// SList class
	/// Holds a series of nodes containing a data type that point to another node in the list, starting with the head and ending with the tail
	/// </summary>
	template <typename T>
	class SList
	{
	private:

		/// <summary>
		/// Helper class for SList
		/// Each element of the list
		/// Stores the peice of data, and the pointer to the next node
		/// </summary>
		/// <returns>A node</returns>
		struct Node final
		{
			/// <summary>
			/// constructor for the node helper class
			/// sets the value of the node and the next node to nullptr
			/// </summary>
			/// <param name="value">The value of the node</param>
			Node(const T& value, Node* next = nullptr);

			/// <summary>
			/// move constructor for the node helper class
			/// sets the value of the node and the next node to nullptr
			/// </summary>
			/// <param name="value">The value of the node</param>
			Node(T&& value, Node* next = nullptr);

			/// <summary>
			/// the value of the node.
			/// </summary>
			T m_NodeValue;

			/// <summary>
			/// the pointer to the next node in the list
			/// </summary>
			Node* m_NextNode = nullptr;
		};
	
	public:
		/// <summary>
		/// Regular iterator for SList
		/// can move through the list, find, insert, and remove nodes
		/// </summary>
		class Iterator final
		{
			friend SList;
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
			Iterator(const Iterator& ToCopy) = default;

			/// <summary>
			/// default move constructor for Iterator
			/// </summary>
			/// <param name="ToMove">the iterator to be moved</param>
			/// <returns>the iterator in its new location</returns>
			Iterator(Iterator&& ToMove) noexcept= default;

			/// <summary>
			/// default copy assignment operator for Iterator
			/// </summary>
			/// <param name="ToCopy">the iterator to be copied</param>
			/// <returns>the freshly copied iterator</returns>
			Iterator& operator=(const Iterator& ToCopy) = default;

			/// <summary>
			/// default move assignment operator for Iterator
			/// </summary>
			/// <param name="ToMove">the iterator to be moved</param>
			/// <returns>teh iterator in its new location</returns>
			Iterator& operator=(Iterator&& ToMove) noexcept = default;

			/// <summary>
			/// default destructor for Iterator
			/// </summary>
			~Iterator() = default;

			/// <summary>
			/// == operator for Iterator
			/// </summary>
			/// <param name="other">the iterator being compared</param>
			/// <returns>whether or not the iterators being compared are equal</returns>
			bool operator==(const Iterator& other) const;

			/// <summary>
			/// not equal operator for Iterator
			/// </summary>
			/// <param name="other">the iterator being compared</param>
			/// <returns>whether or not the iterators being compared are not equal</returns>
			bool operator!=(const Iterator& other) const;

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
			Iterator& operator++(int);

			/// <summary>
			/// dereference operator for iterator
			/// </summary>
			/// <returns>the value of the node being pointed to</returns>
			/// <exception cref="std::runtime_error">throws exception if attempting to dereference a nullptr</exception>
			T& operator*() const;

		private:
			/// <summary>
			/// special iterator constructor that takes a node to point to, and sets the owner
			/// </summary>
			/// <param name="owner">the list that owns the iterator</param>
			/// <param name="node">the node the iterator is to point to</param>
			Iterator(const SList& owner,  Node* node);

			/// <summary>
			/// the owner of the iterator
			/// </summary>
			const SList* m_Owner = nullptr;

			/// <summary>
			/// the node the iterator is pointing to 
			/// </summary>
			Node* m_Node = nullptr;
		};

		/// <summary>
		/// constant version of the iterator class
		/// </summary>
		class ConstIterator final
		{
			friend SList;

		public:
			/// <summary>
			/// default constructor for ConstIterator
			/// </summary>
			ConstIterator() = default;

			/// <summary>
			/// takes a non-const iterator and makes a const version
			/// </summary>
			/// <param name="other">the iterator as a ConstIterator</param>
			ConstIterator(const Iterator& other);

			/// <summary>
			/// default copy constructor for CostIterator
			/// </summary>
			/// <param name="ToCopy">the ConstIterator to be copied</param>
			ConstIterator(const ConstIterator& ToCopy) = default;

			/// <summary>
			/// default move constructor for ConstIterator
			/// </summary>
			/// <param name="ToMove">the ConstIterator to be moved</param>
			/// <returns>the const iterator in its new location</returns>
			ConstIterator(ConstIterator&& ToMove) noexcept = default;

			/// <summary>
			/// default copy assignment operator for ConstIterator
			/// </summary>
			/// <param name="ToCopy">the iterator to be copied</param>
			/// <returns>the freshly copied iterator</returns>
			ConstIterator& operator=(const ConstIterator& ToCopy) = default;

			/// <summary>
			/// default move assignment operator for ConstIterator
			/// </summary>
			/// <param name="ToCopy">the iterator to be moved</param>
			/// <returns>the freshly moved iterator</returns>
			ConstIterator& operator=(ConstIterator&& ToMove) noexcept = default;

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
			/// <param name="other">the ConstIterators being compared</param>
			/// <returns>whether or not the ConstIterators being compared are not equal</returns>
			bool operator!=(const ConstIterator & other) const;

			/// <summary>
			/// prefix incrementor for ConstIterator
			/// moves the iterator to the next node
			/// </summary>
			/// <returns>the iterator in its new location</returns>
			/// <exception cref="std::runtime_error">throws an exception if the iterator has no owner</exception>
			ConstIterator& operator++();

			/// <summary>
			/// prefix incrementor for ConstIterator
			/// moves the iterator to the next node
			/// </summary>
			/// <returns>the iterator in its new location</returns>
			ConstIterator& operator++(int);

			/// <summary>
			/// dereference operator for CosntIterator
			/// </summary>
			/// <returns>the value of the node being pointed to</returns>
			/// <exception cref="std::runtime_error">throws exception if attempting to dereference a nullptr</exception>
			const T& operator*() const;

		private:
			/// <summary>
			/// special ConstIterator constructor that takes a node to point to, and sets the owner
			/// </summary>
			/// <param name="owner">the list that owns the iterator</param>
			/// <param name="node">the node the iterator is to point to</param>
			ConstIterator(const SList & owner, Node * node);

			/// <summary>
			/// the owner of the iterator
			/// </summary>
			const SList* m_Owner = nullptr;

			/// <summary>
			/// the node the iterator is pointing to
			/// </summary>
			const Node* m_Node = nullptr;
		};

		/// <summary>
		/// constructor for SList
		/// sets the head and tail to nullptr and the size to 0
		/// </summary>
		SList();

		/// <summary>
		/// copy constructor for SList
		/// copies all the nodes from the original list into the new one
		/// </summary>
		/// <param name="ToCopy">the list to be copied</param>
		SList(const SList& ToCopy);

		/// <summary>
		/// move constructor for SList
		/// takes m_Head and m_Tail and gives them to the new guy, as well as setting the size
		/// sets the head and tail to nullptr on the original, and makes the size 0
		/// </summary>
		/// <param name="ToMove">the list to be moved</param>
		/// <returns>the moved SList</returns>
		SList(SList&& ToMove) noexcept;

		/// <summary>
		/// destructor for slist
		/// calls clear
		/// </summary>
		~SList();

		/// <summary>
		/// override for assignment operator
		/// essentially does what the copy constructor does but on an already existent object
		/// </summary>
		/// <param name="ToCopy">the list to be copied</param>
		/// <returns>the new list</returns>
		SList& operator=(const SList& ToCopy);

		/// <summary>
		/// move operator
		/// does what the move constructor does but on an already existent object
		/// </summary>
		/// <param name="ToMove">the list to be moved</param>
		/// <returns>the moved list</returns>
		SList& operator=(SList&& ToMove) noexcept;

		/// <summary>
		/// returns the first node in the list (m_Head)
		/// </summary>
		/// <returns>first node of the list</returns>
		/// <exception cref="std::runtime_error">throws an exception if the list is null</exception>
		T& Front();

		/// <summary>
		/// the const version of Front()
		/// </summary>
		/// <returns>first node of the list</returns>
		/// <exception cref="std::runtime_error">throws an exception if the list is null</exception>

		const T& Front() const;

		/// <summary>
		/// returns the last node in the list (m_Tail)
		/// </summary>
		/// <returns>last node of the list</returns>
		/// <exception cref="std::runtime_error">throws an exception if the list is null</exception>
		T& Back();

		/// <summary>
		/// the const version of Back()
		/// </summary>
		/// <returns>last node of the list</returns>
		/// <exception cref="std::runtime_error">throws an exception if the list is null</exception>
		const T& Back() const;

		/// <summary>
		/// pushes a node to the front of the list
		/// takes in a piece of data, creates a node with it, and puts it in the front
		/// </summary>
		/// <param name="ToPush">the data that will be pushed</param>
		Iterator PushFront(const T& ToPush);
	
		/// <summary>
		/// removes the first node in the array
		/// sets the head to be whatever is next
		/// </summary>
		void PopFront();

		/// <summary>
		/// adds a node to the end of the array
		/// takes in a piece of data, creates a node with it, and puts it at the end
		/// </summary>
		/// <param name="ToPush">the data that will be pushed</param>
		Iterator PushBack(const T& ToPush);

		/// <summary>
		/// move version of pushback
		/// adds a node to the end of the array
		/// takes in a piece of data, creates a node with it, and puts it at the end
		/// </summary>
		/// <param name="ToPush">the data that will be pushed</param>
		Iterator PushBack(T&& ToPush);

		/// <summary>
		/// removes the last node of the list
		/// sets the tail to be whatever came before
		/// </summary>
		void PopBack();

		/// <summary>
		/// returns the size of the list (m_Size)
		/// </summary>
		/// <returns>m_Size</returns>
		size_t Size() const;

		/// <summary>
		/// checks to see whether or not the list was empty
		/// </summary>
		/// <returns>true if the list is empty, false if it is not</returns>
		bool IsEmpty() const;

		/// <summary>
		/// removes every element of the list
		/// </summary>
		void Clear();

		/// <summary>
		/// initializes an Iterator pointing at the head of the list
		/// </summary>
		/// <returns>the new Iterator</returns>
		Iterator begin();

		/// <summary>
		/// returns an Iterator pointing past the end of the list (nullptr)
		/// </summary>
		/// <returns>the new iterator</returns>
		Iterator end();

		// <summary>
		/// initializes a ConstIterator pointing at the head of the list
		/// </summary>
		/// <returns>the new ConstIterator</returns>
		ConstIterator begin() const;

		// <summary>
		/// initializes a ConstIterator pointing past the end of the list (nullptr)
		/// </summary>
		/// <returns>the new ConstIterator</returns>
		ConstIterator end() const;

		/// <summary>
		/// initializes a ConstIterator pointing at the head out of a non-const list
		/// </summary>
		/// <returns>the new ConstIterator</returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// initializes a ConstIterator pointing past the end of a non-const list
		/// </summary>
		/// <returns>the new ConstIterator</returns>
		ConstIterator cend() const;

		/// <summary>
		/// Finds the given value in the list
		/// </summary>
		/// <param name="value">the value to be found</param>
		/// <returns>an Iterator pointing at the value in the list, or nullptr if its not there</returns>
		template <typename EqualityFunctor = DefaultEquality<T>>
		Iterator Find(const T& value);

		/// <summary>
		/// Finds the given value in the list
		/// </summary>
		/// <param name="value">the value to be found</param>
		/// <returns>a ConstIterator pointing at the value in the list, or nullptr if its not there</returns>
		template <typename EqualityFunctor = DefaultEquality<T>>
		ConstIterator Find(const T& value) const;

		/// <summary>
		/// inserts a value after the given position in the list
		/// </summary>
		/// <param name="it">the location to be inserted after</param>
		/// <param name="value">the value to be inserted</param>
		/// <returns>the iterator pointing at the new value</returns>
		/// <exception cref="std::runtime_error">throws exception if the iterator has no owner</exception>
		Iterator InsertAfter(Iterator& it, const T& value);

		/// <summary>
		/// removes a given value from the list
		/// </summary>
		/// <param name="value">the value to be removed</param>
		/// <returns>true if the value was successfully removed, false if it was not </returns>
		template <typename EqualityFunctor = DefaultEquality<T>>
		bool Remove(const T& value);

		/// <summary>
		/// removes the node at the given position
		/// </summary>
		/// <param name="it">the iterator at the position to remove</param>
		/// <returns>true if the node was removed, false if it was not</returns>
		bool Remove(const Iterator& it);

	private:
		/// <summary>
		/// the first node of the list
		/// </summary>
		Node* m_Head;

		/// <summary>
		/// the last node of the list
		/// </summary>
		Node* m_Tail;

		/// <summary>
		/// the size of the list
		/// </summary>
		size_t m_Size;
	};
}

#include "SList.inl"