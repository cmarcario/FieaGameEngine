#pragma once
#include "DefaultEquality.h"
#include "DefaultIncrement.h"

namespace FieaGameEngine
{
	/// <summary>
	/// vector class
	/// holds data in an array-like structure, that can be resized as necessary.
	/// </summary>
	/// <typeparam name="T">the type of data to be stored in the container</typeparam>
	template <typename T>
	class Vector
	{
	public:
		class Iterator
		{
			friend Vector;
			friend class ConstIterator;

		public:
			using size_type = size_t;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using reference = T;
			using pointer = T*;
			using iterator_category = std::forward_iterator_tag;

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
			/// <exception cref="std::runtime_error">throws an exception if the iterator has no owner</exception>
			Iterator& operator++();

			/// <summary>
			/// postfix incrementor for iterator
			/// moves the iterator to the next index
			/// </summary>
			/// <returns>the iterator in its new location</returns>
			Iterator operator++(int);

			/// <summary>
			/// dereference operator for iterator
			/// </summary>
			/// <returns>the value of the node being pointed to</returns>
			/// <exception cref="std::runtime_error">throws exception if attempting to dereference a nullptr</exception>
			T& operator*() const;

			/// <summary>
			/// arrow dereference operator for iterator
			/// </summary>
			/// <returns>the value of the node being pointed to</returns>
			/// <exception cref="std::runtime_error">throws exception if attempting to dereference a nullptr</exception>
			T* operator->() const;

		private:
			/// <summary>
			/// special iterator constructor that takes a node to point to, and sets the owner
			/// </summary>
			/// <param name="owner">the list that owns the iterator</param>
			/// <param name="index">the index the iterator is to point to</param>
			Iterator(Vector & owner, size_t index);

			/// <summary>
			/// the owner of the iterator
			/// </summary>
			Vector* m_Owner = nullptr;

			/// <summary>
			/// the index the iterator is pointing to 
			/// </summary>
			size_t m_Index = 0_z;
		};

		class ConstIterator
		{
			friend Vector;

		public:
			using size_type = size_t;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using reference = T;
			using pointer = T*;
			using iterator_category = std::forward_iterator_tag;

			/// <summary>
			/// default constructor for Iterator
			/// </summary>
			ConstIterator() = default;

			/// <summary>
			/// default copy constructor for ConstIterator
			/// </summary>
			/// <param name="ToCopy">the ConstIterator to be copied</param>
			ConstIterator(const ConstIterator& ToCopy) = default;

			/// <summary>
			/// returns a const iterator made out of a regular iterator.
			/// </summary>
			/// <param name="other">the iterator to make a new const iterator with</param>
			ConstIterator(const Iterator& other);

			/// <summary>
			/// default move constructor for ConstIterator
			/// </summary>
			/// <param name="ToMove">the ConstIterator to be moved</param>
			/// <returns>the ConstIterator in its new location</returns>
			ConstIterator(ConstIterator&& ToMove) noexcept = default;

			/// <summary>
			/// default copy assignment operator for ConstIterator
			/// </summary>
			/// <param name="ToCopy">the ConstIterator to be copied</param>
			/// <returns>the freshly copied ConstIterator</returns>
			ConstIterator& operator=(const ConstIterator& ToCopy) = default;

			/// <summary>
			/// default move assignment operator for ConstIterator
			/// </summary>
			/// <param name="ToMove">the ConstIterator to be moved</param>
			/// <returns>teh ConstIterator in its new location</returns>
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
			bool operator==(const ConstIterator& other) const;

			/// <summary>
			/// not equal operator for ConstIterator
			/// </summary>
			/// <param name="other">the ConstIterator being compared</param>
			/// <returns>whether or not the ConstIterators being compared are not equal</returns>
			bool operator!=(const ConstIterator& other) const;

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
			const T& operator*() const;

		private:
			/// <summary>
			/// special ConstIterator constructor that takes a node to point to, and sets the owner
			/// </summary>
			/// <param name="owner">the list that owns the ConstIterator</param>
			/// <param name="index">the index the ConstIterator is to point to</param>
			ConstIterator(const Vector& owner, size_t index);

			/// <summary>
			/// the owner of the ConstIterator
			/// </summary>
			const Vector* m_Owner = nullptr;

			/// <summary>
			/// the index the ConstIterator is pointing to 
			/// </summary>
			size_t m_Index = 0;
		};

		/// <summary>
		/// constructor for vector.
		/// does not reserve on default, but does reserve a capacity if one is passed in.
		/// </summary>
		/// <param name="capacity">the capacity to be set upon construction, if any</param>
		Vector(size_t capacity  = size_t(0));

		/// <summary>
		/// constructor for vector that takes an initial list of values
		/// reserves the amount of spaces required, and then pushes back the values in the list
		/// </summary>
		/// <param name="list">list of values to be added to the vector</param>
		Vector(std::initializer_list<T> list);

		/// <summary>
		/// copy constructor for vector
		/// reserves the same capacity that the vector to be copied has, then pushes back copies of the values from that list
		/// </summary>
		/// <param name="ToCopy">the vector to be copied</param>
		Vector(const Vector& ToCopy);

		/// <summary>
		/// move constructor for vector
		/// takes the pointer to the incoming vectors data, ands sets the size and capacity to be equal to that vectors
		/// sets the incoming vectors data to null and the size and capacity to 0
		/// </summary>
		/// <param name="ToMove">the vector to be moved</param>
		/// <returns>the freshly moved vector</returns>
		Vector(Vector&& ToMove) noexcept;

		/// <summary>
		/// destructor for vector
		/// calls clear, then frees the memory for the overall array
		/// </summary>
		~Vector();

		/// <summary>
		/// copy assignment operator for vector
		/// does what the copy constructor does but for an already existing vector
		/// however, if the already existing vector has a higher capacity than the incoming vector, it will be left alone
		/// </summary>
		/// <param name="ToCopy">the vector to be copied</param>
		/// <returns>the freshly copied vector</returns>
		Vector& operator=(const Vector& ToCopy);

		/// <summary>
		/// move assignment operator for vector
		/// does what the move constructor does, but for an already existent vector
		/// </summary>
		/// <param name="ToMove">the vector to be moved</param>
		/// <returns></returns>
		Vector& operator=(Vector&& ToMove) noexcept;

		/// <summary>
		/// [] operator for movement
		/// returns the element at the given index, if it is within bounds
		/// </summary>
		/// <param name="index">the index to retrieve the data at</param>
		/// <returns>the data at the given index</returns>
		/// <exception cref="runtime_error">throws an exception if the vector is empty</exception>
		/// <exception cref="runtime_error">throws an exception if the index is out of bounds</exception>
		T& operator[](size_t index);

		/// <summary>
		/// const [] operator for movement
		/// returns the element at the given index, if it is within bounds
		/// </summary>
		/// <param name="index">the index to retrieve the data at</param>
		/// <returns>the data at the given index</returns>
		/// <exception cref="runtime_error">throws an exception if the vector is empty</exception>
		/// <exception cref="runtime_error">throws an exception if the index is out of bounds</exception>
		const T& operator[](size_t index) const;

		/// <summary>
		/// returns the value at the given index
		/// </summary>
		/// <param name="index">the index to retrieve the data at</param>
		/// <returns>the data at the given index</returns>
		T& At(size_t index);

		/// <summary>
		/// returns the value at the given index, const
		/// </summary>
		/// <param name="index">the index to retrieve the data at</param>
		/// <returns>the data at the given index</returns>
		const T& At(size_t index) const;

		/// <summary>
		/// returns the first element in the vector
		/// </summary>
		/// <returns>the first element in the vector</returns>
		const T& Front() const;

		/// <summary>
		/// returns the first element in the vector, const
		/// </summary>
		/// <returns>the first element in the vector</returns>
		T& Front();

		/// <summary>
		/// returns the last element in the vector
		/// </summary>
		/// <returns>the last element in the vector</returns>
		const T& Back() const;

		/// <summary>
		/// returns the last element in the vector
		/// </summary>
		/// <returns>the last element in the vector</returns>
		T& Back();

		/// <summary>
		/// returns whether or not the vector is empty
		/// </summary>
		/// <returns>whether or not the vector is empty</returns>
		bool IsEmpty() const;

		/// <summary>
		/// returns the size of the vector, i.e., the number of elements 
		/// </summary>
		/// <returns>the size of the vector</returns>
		size_t Size() const;

		/// <summary>
		/// returns the capacity of the vector, i.e., how many elements it can currently hold
		/// </summary>
		/// <returns>the capacity of the vector</returns>
		size_t Capacity() const;

		/// <summary>
		/// adds the given value to the end of the vector and increments size
		/// if out of space, more is reserved based on the increment functor
		/// </summary>
		/// <param name="value">the value to be added</param>
		/// <returns>an iterator pointing at the newly added value</returns>
		template <typename IncrementFunctor = DefaultIncrement>
		Iterator PushBack(const T& value);

		/// <summary>
		/// adds the given value to the end of the vector and increments size
		/// if out of space, more is reserved based on the increment functor
		/// uses an rvalue reference as opposed to lvalue
		/// </summary>
		/// <param name="value">the value to be added</param>
		/// <returns>an iterator pointing at the newly added value</returns>
		template <typename IncrementFunctor = DefaultIncrement>
		Iterator PushBack(T&& value);

		/// <summary>
		/// removes the last element from the list
		/// does NOT change the size of the capacity
		/// </summary>
		void PopBack();

		/// <summary>
		/// reserves the given amount of space
		/// </summary>
		/// <param name="capacity"></param>
		void Reserve(size_t capacity);

		/// <summary>
		/// reduces the capacity of the vector to match the size
		/// </summary>
		void ShrinkToFit();

		/// <summary>
		/// clears the elements from the vector
		/// does NOT change the size of the capacity
		/// </summary>
		void Clear();

		/// <summary>
		/// creates an iterator at the beginning of the vector
		/// </summary>
		/// <returns>the new iterator</returns>
		Iterator begin();

		/// <summary>
		/// creates an iterator past the end of the vector
		/// </summary>
		/// <returns>the new iterator</returns>
		Iterator end();

		/// <summary>
		/// creates a ConstIterator at the beginning of the vector
		/// </summary>
		/// <returns>the new ConstIterator</returns>
		ConstIterator begin() const;

		/// <summary>
		/// creates an ConstIterator past the end of the vector
		/// </summary>
		/// <returns>the new ConstIterator</returns>
		ConstIterator end() const;

		/// <summary>
		/// creates a ConstIterator at the beginning of the vector
		/// can be created out of a regular iterator
		/// </summary>
		/// <returns>the new ConstIterator</returns>>
		ConstIterator cbegin() const;

		/// <summary>
		/// creates an ConstIterator past the end of the vector
		/// can be created out of a regular iterator
		/// </summary>
		/// <returns>the new ConstIterator</returns>
		ConstIterator cend() const;

		/// <summary>
		/// finds a given value within the vector and returns an iterator pointing at that address
		/// </summary>
		/// <param name="value">the value to be found</param>
		/// <returns>an iterator with the index of the value, or with the index at size if it was not found</returns>
		template <typename EqualityFunctor = DefaultEquality<T>>
		Iterator Find(const T& value);

		/// <summary>
		/// const version of find
		/// finds a given value within the vector and returns a ConstIterator pointing at that address
		/// </summary>
		/// <param name="value">the value to be found</param>
		/// <returns>a ConstIterator with the index of the value, or with the index at size if it was not found</returns>
		template <typename EqualityFunctor = DefaultEquality<T>>
		ConstIterator Find(const T& value) const;

		/// <summary>
		/// removes the given value from the vector
		/// does NOT lower the capacity of the vector
		/// </summary>
		/// <param name="ToRemove">the value to be removed</param>
		/// <returns>whether or not the value was successfully removed</returns>
		template <typename EqualityFunctor = DefaultEquality<T>>
		bool Remove(const T& ToRemove);

		/// <summary>
		/// removes the value at the iterator's index from the vector
		/// does NOT lower the capacity of the vector
		/// </summary>
		/// <param name="ToRemove">the index</param>
		/// <returns>whether or not the value was successfully removed</returns>
		/// <exception cref="runtime_error">throws an exception if the iteratror is not owned by the list it is trying to remove from</exception>
		bool Remove(const Iterator& it);

		/// <summary>
		/// removes the given range of elements from the vector
		/// does NOT lower the capacity of the vector
		/// </summary>
		/// <param name="startIt">the first element to be removed</param>
		/// <param name="endIt">the last element to be removed</param>
		/// <returns>whenter or not the elements were successfully removed</returns>
		/// <exception cref="runtime_error">throws an exception if either iteratror is not owned by the list it is trying to remove from</exception>
		void Remove(const Iterator& startIt, const Iterator& endIt);

	private:
		/// <summary>
		/// the pointer to the beginning of the vector
		/// </summary>
		T* m_Data = nullptr; 

		/// <summary>
		/// the number of elements in the vector
		/// </summary>
		size_t m_Size = 0;

		/// <summary>
		/// the maximum size of the vector
		/// </summary>
		size_t m_Capacity = 0;
	};
}

#include "Vector.inl"

