#include "pch.h"
#include <initializer_list>
#include <cassert>
#include "Vector.h"
#include "DefaultEquality.h"

namespace FieaGameEngine
{
#pragma region Vector
	template<typename T>
	inline Vector<T>::Vector(size_t capacity)
	{
		if (capacity > 0)
		{
			Reserve(capacity);
		}
	}

	template<typename T>
	Vector<T>::Vector(std::initializer_list<T> list)
	{
		Reserve(list.size());
		for (const auto& value : list)
		{
			new(m_Data + m_Size++)T(value);
		}
	}

	template<typename T>
	Vector<T>::Vector(const Vector& ToCopy)
	{
		Reserve(ToCopy.Capacity());
		for (const auto& value : ToCopy)
		{
			new(m_Data + m_Size++)T(value);
		}
	}

	template<typename T>
	Vector<T>::Vector(Vector&& ToMove) noexcept :
		m_Data(ToMove.m_Data), m_Size(ToMove.m_Size), m_Capacity(ToMove.m_Capacity)
	{
		ToMove.m_Data = nullptr;
		ToMove.m_Size = size_t(0);
		ToMove.m_Capacity = size_t(0);
	}

	template<typename T>
	Vector<T>& Vector<T>::operator=(const Vector& ToCopy)
	{
		if (this != &ToCopy)
		{
			Clear();
			if (m_Capacity < ToCopy.Capacity())
			{
				Reserve(ToCopy.Capacity());
			}

			for (const auto& value : ToCopy)
			{
				new(m_Data + m_Size++)T(value);
			}
		}

		return *this;
	}

	template<typename T>
	Vector<T>& Vector<T>::operator=(Vector&& ToMove) noexcept
	{
		if (this != &ToMove)
		{
			Clear();
			free(m_Data);

			m_Data = ToMove.m_Data;
			m_Size = ToMove.m_Size;
			m_Capacity = ToMove.m_Capacity;

			ToMove.m_Data = nullptr;
			ToMove.m_Size = size_t(0);
			ToMove.m_Capacity = size_t(0);
		}

		return *this;
	}

	template<typename T>
	T& Vector<T>::operator[](size_t index)
	{
		if (index >= m_Size)
		{
			throw(std::runtime_error("Index is out of bounds"));
		}
		return m_Data[index];
	}

	template<typename T>
	const T& Vector<T>::operator[](size_t index) const
	{
		if (index >= m_Size)
		{
			throw(std::runtime_error("Index is out of bounds"));
		}
		return m_Data[index];
	}

	template<typename T>
	inline T& Vector<T>::At(size_t index)
	{
		return operator[](index);
	}

	template<typename T>
	inline const T& Vector<T>::At(size_t index) const
	{
		return operator[](index);
	}

	template<typename T>
	inline const T& Vector<T>::Front() const
	{
		if (m_Size == 0_z)
		{
			throw std::runtime_error("m_Data is null! Have you pushed any data, cleared the vectpr, or moved this instance?");
		}

		return m_Data[0];
	}

	template<typename T>
	inline T& Vector<T>::Front()
	{
		if (m_Size == 0_z)
		{
			throw std::runtime_error("m_Data is null! Have you pushed any data, cleared the vectpr, or moved this instance?");
		}

		return m_Data[0];
	}

	template<typename T>
	inline const T& Vector<T>::Back() const
	{
		if (m_Size == 0_z)
		{
			throw std::runtime_error("m_Data is null! Have you pushed any data, cleared the vectpr, or moved this instance?");
		}

		return m_Data[m_Size - 1];
	}

	template<typename T>
	inline T& Vector<T>::Back()
	{
		if (m_Size == 0_z)
		{
			throw std::runtime_error("m_Data is null! Have you pushed any data, cleared the vectpr, or moved this instance?");
		}

		return m_Data[m_Size - 1];
	}

	template<typename T>
	inline bool Vector<T>::IsEmpty() const
	{
		return (m_Size == size_t(0));
	}

	template<typename T>
	inline size_t Vector<T>::Size() const
	{
		return m_Size;
	}

	template<typename T>
	inline size_t Vector<T>::Capacity() const
	{
		return m_Capacity;
	}

	template<typename T>
	template <typename IncrementFunctor>
	typename Vector<T>::Iterator Vector<T>::PushBack(const T& value)
	{
		if (m_Size == m_Capacity)
		{
			IncrementFunctor increment;
			size_t increaseBy = increment(m_Size, m_Capacity);
			
			size_t capacity = m_Capacity + std::max(size_t(1), increaseBy);

			Reserve(capacity);
		}

		new(m_Data + m_Size)T(value);

		return Iterator(*this, m_Size++);
	}

	template<typename T>
	template <typename IncrementFunctor>
	typename Vector<T>::Iterator Vector<T>::PushBack(T&& value)
	{
		if (m_Size == m_Capacity)
		{
			IncrementFunctor increment;
			size_t increaseBy = increment(m_Size, m_Capacity);

			size_t capacity = m_Capacity + std::max(size_t(1), increaseBy);

			Reserve(capacity);
		}

		new(m_Data + m_Size)T(std::move(value));

		return Iterator(*this, m_Size++);
	}

	template<typename T>
	inline void Vector<T>::PopBack()
	{
		if (m_Size > 0)
		{
			m_Data[m_Size - 1].~T();
			--m_Size;
		}
	}

	template <typename T>
	void Vector<T>::Reserve(size_t capacity)
	{
		if (capacity > m_Capacity)
		{
			T* data = reinterpret_cast<T*>(realloc(m_Data, sizeof(T) * capacity));
			assert(data != nullptr);
			m_Data = data;
			m_Capacity = capacity;
		}
	}

	template<typename T>
	inline void Vector<T>::ShrinkToFit()
	{
		if (m_Size < m_Capacity)
		{
			if (m_Size == 0)
			{
				free(m_Data);
				m_Capacity = 0;
				m_Data = nullptr;
			}
			else
			{
				T* data = reinterpret_cast<T*>(realloc(m_Data, sizeof(T) * m_Size));
				assert(data != nullptr);
				m_Data = data;
				m_Capacity = m_Size;
			}
		}
	}

	template <typename T>
	void Vector<T>::Clear()
	{
		for (size_t i = 0; i < m_Size; ++i)
		{
			m_Data[i].~T();
		}

		m_Size = size_t(0);
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::begin()
	{
		return Iterator(*this, size_t(0));
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::end()
	{
		return Iterator(*this, m_Size);
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::begin() const
	{
		return ConstIterator(*this, size_t(0));
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::end() const
	{
		return ConstIterator(*this, m_Size);
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::cbegin() const
	{
		return ConstIterator(*this, size_t(0));
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::cend() const
	{
		return ConstIterator(*this, m_Size);
	}

	template<typename T>
	template <typename EqualityFunctor>
	inline bool Vector<T>::Remove(const T& ToRemove)
	{
		Iterator it = Find<EqualityFunctor>(ToRemove);
		return Remove(it);
	}

	template<typename T>
	bool Vector<T>::Remove(const Iterator& it)
	{
		bool removed = false;

		if (it.m_Owner != this)
		{ 
			throw std::runtime_error("Container does not own this iterator");
		}

		if (it.m_Index == m_Size - 1)
		{
			PopBack();
		}

		if (it.m_Index >= 0 && it.m_Index < m_Size)
		{
			T* destination = m_Data + (it.m_Index);
			T* source = destination + size_t(1);
			size_t count = (m_Size - (it.m_Index + 1)) * sizeof(T);

			m_Data[it.m_Index].~T();

			memmove(destination, source, count);
			--m_Size;
			removed = true;
		}

		return removed;
	}

	template<typename T>
	void Vector<T>::Remove(const Iterator& startIt, const Iterator& endIt)
	{
		if (startIt.m_Owner != this || endIt.m_Owner != this)
		{
			throw std::runtime_error("Container does not own both iterators");
		}

		if (startIt.m_Index >= 0 && startIt.m_Index < m_Size)
		{
			if (endIt.m_Index >= 0 && endIt.m_Index <= m_Size)
			{
				T* destination = m_Data + startIt.m_Index;
				T* source = m_Data + endIt.m_Index;
				size_t count = (m_Size - endIt.m_Index + 1) * sizeof(T);

				for (size_t i = startIt.m_Index; i < endIt.m_Index; ++i)
				{
					m_Data[i].~T();
					--m_Size;
				}

				if (endIt != endIt.m_Owner->end())
				{
					memmove(destination, source, count);
				}
			}
		}
	}

	template<typename T>
	template<typename EqualityFunctor>
	typename Vector<T>::Iterator Vector<T>::Find(const T& value)
	{
		EqualityFunctor eq;
		Iterator it = begin();
		for (it; it != end(); ++it)
		{
			if (eq(*it, value))
			{
				break;
			}
		}

		return it;
	}

	template<typename T>
	template<typename EqualityFunctor>
	typename Vector<T>::ConstIterator Vector<T>::Find(const T& value) const
	{
		EqualityFunctor eq;
		ConstIterator it = begin();
		for (it; it != end(); ++it)
		{
			if (eq(*it, value))
			{
				break;
			}
		}

		return it;
	}

	template<typename T>
	inline Vector<T>::~Vector()
	{
		if (m_Capacity > 0)
		{
			Clear();
			free(m_Data);
		}
	}
#pragma endregion Vector

#pragma region Iterator
	template <typename T>
	inline Vector<T>::Iterator::Iterator(Vector& owner, size_t index) :
		m_Owner(&owner), m_Index(index){ }

	template <typename T>
	inline bool Vector<T>::Iterator::operator==(const Iterator& other) const
	{
		return !(operator!=(other));
	}

	template <typename T>
	inline bool Vector<T>::Iterator::operator!=(const Iterator& other) const
	{
		return m_Owner != other.m_Owner || m_Index != other.m_Index;
	}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		if (m_Owner == nullptr)
		{
			throw std::runtime_error("Unassociated iterator");
		}

		if (m_Index < m_Owner->Size())
		{
			++m_Index;
		}
		return *this;
	}

	template <typename T>
	inline typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		Iterator tempo = *this;
		operator++();
		return tempo;
	}

	template <typename T>
	inline T& Vector<T>::Iterator::operator*() const
	{
		if (m_Owner == nullptr)
		{
			throw std::runtime_error("Unassociated Iterator");
		}

		return m_Owner->At(m_Index);
	}

	template <typename T>
	inline T* Vector<T>::Iterator::operator->() const
	{
		return &(operator*());
	}

#pragma endregion Iterator

#pragma region ConstIterator
	template <typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const Vector& owner, size_t index) :
		m_Owner(&owner), m_Index(index) { }

	template <typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const Iterator& other) :
		m_Owner(other.m_Owner), m_Index(other.m_Index) { }

	template <typename T>
	inline bool Vector<T>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return !(operator!=(other));
	}

	template <typename T>
	inline bool Vector<T>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return m_Owner != other.m_Owner || m_Index != other.m_Index;
	}

	template <typename T>
	typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator++()
	{
		if (m_Owner == nullptr)
		{
			throw std::runtime_error("Unassociated iterator");
		}
		
		if (m_Index < m_Owner->Size())
		{
			++m_Index;
		}

		return *this;
	}

	template <typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator++(int)
	{
		ConstIterator tempo = *this;
		operator++();
		return tempo;
	}

	template <typename T>
	inline const T& Vector<T>::ConstIterator::operator*() const
	{
		if (m_Owner == nullptr)
		{
			throw std::runtime_error("Unassociated Iterator");
		}

		return m_Owner->At(m_Index);
	}

#pragma endregion ConstIterator
}
