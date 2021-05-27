#include "SList.h"

namespace FieaGameEngine 
{
#pragma region SList
	template<typename T>
	inline SList<T>::SList() : m_Head(nullptr), m_Tail(nullptr), m_Size(0) {}

	template<typename T>
	inline SList<T>::SList(const SList& ToCopy)
	{
		for (const T& value : ToCopy)
		{
			PushBack(value);
		}
	}

	template<typename T>
	inline SList<T>::SList(SList&& ToMove) noexcept : 
		m_Head(ToMove.m_Head), m_Tail(ToMove.m_Tail), m_Size(ToMove.m_Size)
	{
		ToMove.m_Head = nullptr;
		ToMove.m_Tail = nullptr;
		ToMove.m_Size = size_t(0);
	}

	template<typename T>
	inline SList<T>& SList<T>::operator=(const SList& ToCopy)
	{
		if (this != &ToCopy)
		{
			Clear();
			for (const T& value : ToCopy)
			{
				PushBack(value);
			}
		}

		return *this;
	}

	template<typename T>
	inline SList<T>& SList<T>::operator=(SList&& ToMove) noexcept
	{
		if (this != &ToMove)
		{
			Clear();

			m_Head = ToMove.m_Head;
			m_Tail = ToMove.m_Tail;
			m_Size = ToMove.m_Size;

			ToMove.m_Head = nullptr;
			ToMove.m_Tail = nullptr;
			ToMove.m_Size = size_t(0);
		}

		return *this;
	}

	template<typename T>
	inline T& SList<T>::Front()
	{
		if (m_Head == nullptr)
		{
			throw std::runtime_error("m_Head is null! Have you pushed any nodes, cleared the list, or moved this instance?");
		}

		return m_Head->m_NodeValue;
	}

	template<typename T>
	inline const T& SList<T>::Front() const
	{
		if (m_Head == nullptr)
		{
			throw std::runtime_error("m_Head is null! Have you pushed any nodes, cleared the list, or moved this instance?");
		}

		return m_Head->m_NodeValue;
	}

	template<typename T>
	inline T& SList<T>::Back()
	{
		if (m_Tail == nullptr)
		{
			throw std::runtime_error("m_Tail is null! Have you pushed any nodes, cleared the list, or moved this instance?");
		}
		return m_Tail->m_NodeValue;
	}

	template<typename T>
	inline const T& SList<T>::Back() const
	{
		if (m_Tail == nullptr)
		{
			throw std::runtime_error("m_Tail is null! Have you pushed any nodes, cleared the list, or moved this instance?");
		}
		return m_Tail->m_NodeValue;
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::PushFront(const T& ToPush)
	{
		m_Head = new Node(ToPush, m_Head);
		m_Size++;

		if (m_Tail == nullptr)
		{
			m_Tail = m_Head;
		}

		return begin();
	}

	template<typename T>
	inline void SList<T>::PopFront()
	{
		if (m_Head != nullptr)
		{
			Node* PoppedNode = m_Head;
			m_Head = m_Head->m_NextNode;

			if (m_Head == nullptr)
			{
				m_Tail = nullptr;
			}

			delete PoppedNode;
			m_Size--;
		}
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::PushBack(const T& ToPush)
	{
		Node* CurrentTail = m_Tail;

		m_Tail = new Node(ToPush);
		m_Size++;

		if (CurrentTail == nullptr)
		{
			m_Head = m_Tail;
			return begin();
		}
		
		CurrentTail->m_NextNode = m_Tail;
		return Iterator(*this, m_Tail);
		
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::PushBack(T&& ToPush)
	{
		Node* CurrentTail = m_Tail;

		m_Tail = new Node(std::move(ToPush));
		m_Size++;

		if (CurrentTail == nullptr)
		{
			m_Head = m_Tail;
			return begin();
		}

		CurrentTail->m_NextNode = m_Tail;
		return Iterator(*this, m_Tail);

	}

	template<typename T>
	inline void SList<T>::PopBack()
	{
		if (m_Tail != nullptr)
		{
			Node* PoppedNode = m_Tail;
			Node* CurrentNode = m_Head;

			if (m_Head->m_NextNode != nullptr)
			{
				while (CurrentNode->m_NextNode != m_Tail)
				{
					CurrentNode = CurrentNode->m_NextNode;
				}

				m_Tail = CurrentNode;
				m_Tail->m_NextNode = nullptr;
			}
			else
			{
				m_Head = nullptr;
				m_Tail = nullptr;
			}

			delete PoppedNode;
			m_Size--;
		}
	}

	template<typename T>
	inline size_t SList<T>::Size() const
	{
		return m_Size;
	}

	template<typename T>
	inline bool SList<T>::IsEmpty() const
	{
		return (m_Head == nullptr);
	}

	template<typename T>
	inline void SList<T>::Clear()
	{
		while (m_Head != nullptr)
		{
			PopFront();
		}
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::begin()
	{
		return Iterator(*this, m_Head);
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::end()
	{
		return Iterator(*this, nullptr);
	}

	template<typename T>
	inline typename SList<T>::ConstIterator SList<T>::begin() const
	{
		return ConstIterator(*this, m_Head);
	}

	template<typename T>
	inline typename SList<T>::ConstIterator SList<T>::end() const
	{
		return ConstIterator(*this, nullptr);
	}

	template<typename T>
	inline typename SList<T>::ConstIterator SList<T>::cbegin() const
	{
		return ConstIterator(*this, m_Head);
	}

	template<typename T>
	inline typename SList<T>::ConstIterator SList<T>::cend() const
	{
		return ConstIterator(*this, nullptr);
	}

	template<typename T>
	template<typename EqualityFunctor>
	inline typename SList<T>::Iterator SList<T>::Find(const T& value)
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
	inline typename SList<T>::ConstIterator SList<T>::Find(const T& value) const
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
	inline typename SList<T>::Iterator SList<T>::InsertAfter(Iterator& it, const T& value)
	{
		if (it.m_Owner == nullptr)
		{
			throw std::runtime_error("Iterator unassociated");
		}

		if (it.m_Node == nullptr)
		{
			PushBack(value);
			return it;
		}
		
		Node* Next = it.m_Node->m_NextNode;
		it.m_Node->m_NextNode = new Node(value, Next);
		m_Size++;
		++it;
		return it;
		
	}

	template<typename T>
	template <typename EqualityFunctor>
	inline bool SList<T>::Remove(const T& value)
	{
		Iterator it = Find<EqualityFunctor>(value);

		if (it != end())
		{
			return Remove(it);
		}

		return false;
	}

	template<typename T>
	inline bool SList<T>::Remove(const Iterator& it)
	{
		if (it.m_Node != nullptr)
		{
			if (it.m_Node->m_NextNode != nullptr)
			{
				Node* Next = it.m_Node->m_NextNode;
				it.m_Node->m_NodeValue.~T();
				new(&it.m_Node->m_NodeValue)T(std::move(Next->m_NodeValue));
				it.m_Node->m_NextNode = Next->m_NextNode;

				if (it.m_Node->m_NextNode == nullptr)
				{
					m_Tail = it.m_Node;
				}
				delete Next;
				--m_Size;
			}
			else
			{
				PopBack();
			}
			return true;
		}

		return false;
	}


	template <typename T>
	inline SList<T>::~SList()
	{
		Clear();
	}

#pragma endregion SList

	

#pragma region Node
	template<typename T>
	inline SList<T>::Node::Node(const T& value, Node* next) : m_NodeValue(value), m_NextNode(next) {}

	template<typename T>
	inline SList<T>::Node::Node(T&& value, Node* next) : m_NodeValue(value), m_NextNode(next) {}


#pragma region Iterator

	template <typename T>
	inline SList<T>::Iterator::Iterator(const SList& owner, Node* node) : 
		m_Node(node), m_Owner(&owner) { }

	template <typename T>
	inline bool SList<T>::Iterator::operator==(const Iterator& other) const
	{
		return !(operator!=(other));
	}

	template <typename T>
	inline bool SList<T>::Iterator::operator!=(const Iterator& other) const
	{
		return m_Owner != other.m_Owner || m_Node != other.m_Node;
	}

	template <typename T>
	inline typename SList<T>::Iterator& SList<T>::Iterator::operator++()
	{
		if (m_Owner == nullptr)
		{
			throw std::runtime_error("Unassociated iterator");
		}

		if (m_Node != nullptr)
		{
			m_Node = m_Node->m_NextNode;
		}
		return *this;
	}

	template <typename T>
	inline typename SList<T>::Iterator& SList<T>::Iterator::operator++(int)
	{
		Iterator& temp(*this);
		operator++();

		return temp;
	}

	template <typename T>
	inline T& SList<T>::Iterator::operator*() const
	{
		if (m_Node == nullptr)
		{
			throw std::runtime_error("Null reference");
		}

		return m_Node->m_NodeValue;
	}

#pragma endregion Iterator

#pragma region ConstIterator

	template <typename T>
	inline SList<T>::ConstIterator::ConstIterator(const SList& owner, Node* node) :
		m_Node(node), m_Owner(&owner) { }

	template <typename T>
	inline SList<T>::ConstIterator::ConstIterator(const Iterator& other) :
		m_Node(other.m_Node), m_Owner(other.m_Owner) { }

	template <typename T>
	inline bool SList<T>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return !(operator!=(other));
	}

	template <typename T>
	inline bool SList<T>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return m_Owner != other.m_Owner || m_Node != other.m_Node;
	}

	template <typename T>
	inline typename SList<T>::ConstIterator& SList<T>::ConstIterator::operator++()
	{
		if (m_Owner == nullptr)
		{
			throw std::runtime_error("Unassociated ConstIterator");
		}

		if (m_Node != nullptr)
		{
			m_Node = m_Node->m_NextNode;
		}

		return *this;
	}

	template <typename T>
	inline typename SList<T>::ConstIterator& SList<T>::ConstIterator::operator++(int)
	{
		ConstIterator& temp(*this);
		operator++();

		return temp;
	}

	template <typename T>
	inline const T& SList<T>::ConstIterator::operator*() const
	{
		if (m_Node == nullptr)
		{
			throw std::runtime_error("Null reference");
		}

		return m_Node->m_NodeValue;
	}

#pragma endregion ConstIterator
}