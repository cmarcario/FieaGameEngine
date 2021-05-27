#include "pch.h"
#include "Scope.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Scope);

	Scope::Scope(size_t size) : m_Map(size), m_Order(size) {}

	Scope::Scope(const Scope& toCopy)
	{
		for (auto it = toCopy.m_Order.begin(); it != toCopy.m_Order.end(); ++it)
		{
			MapPairType* currentPair = *it;
			Datum& datum = Append(currentPair->first);
			Datum& copyDatum = currentPair->second;
			if (copyDatum.Type() == Datum::DatumTypes::TABLE)
			{
				datum.SetType(Datum::DatumTypes::TABLE);
				for (size_t i = 0; i < copyDatum.Size(); ++i)
				{
					Scope* scope = copyDatum.Get<Scope>(i).Clone();
					scope->m_Parent = this;
					datum.PushBack(*scope);
				}
			}
			else
			{
				datum = copyDatum;
			}
		}
	}

	Scope::Scope(Scope&& toMove) noexcept
	{
		m_Order = std::move(toMove.m_Order);
		m_Map = std::move(toMove.m_Map);
		m_Parent = toMove.m_Parent;

		for (auto it = m_Map.begin(); it != m_Map.end(); ++it)
		{
			Datum& datum = it->second;
			if (datum.Type() == Datum::DatumTypes::TABLE)
			{
				for (size_t i = 0; i < datum.Size(); ++i)
				{
					Scope& scope = datum.Get<Scope>(i);
					scope.m_Parent = this;
				}
			}
		}

		if (m_Parent != nullptr)
		{
			auto [parentDatum, index] = m_Parent->FindContainedScope(toMove);
			parentDatum->Set(*this, index);
			toMove.m_Parent = nullptr;
		}
	}

	Scope& Scope::operator=(const Scope& toCopy)
	{
		if (this != &toCopy)
		{
			Clear();
			for (auto it = toCopy.m_Order.begin(); it != toCopy.m_Order.end(); ++it)
			{
				MapPairType* currentPair = *it;
				Datum& datum = Append(currentPair->first);
				Datum& copyDatum = currentPair->second;

				if (copyDatum.Type() == Datum::DatumTypes::TABLE)
				{
					datum.SetType(Datum::DatumTypes::TABLE);
					for (size_t i = 0; i < copyDatum.Size(); ++i)
					{
						Scope* scope = copyDatum.Get<Scope>(i).Clone();
						scope->m_Parent = this;
						datum.PushBack(*scope);
					}
				}
				else
				{
					datum = copyDatum;
				}
			}
		}

		return *this;
	}

	Scope& Scope::operator=(Scope&& toMove) noexcept
	{
		if (this != &toMove)
		{
			Clear();
			Orphan();

			m_Order = std::move(toMove.m_Order);
			m_Map = std::move(toMove.m_Map);
			m_Parent = toMove.m_Parent;

			for (auto it = m_Map.begin(); it != m_Map.end(); ++it)
			{
				Datum& datum = it->second;
				if (datum.Type() == Datum::DatumTypes::TABLE)
				{
					for (size_t i = 0; i < datum.Size(); ++i)
					{
						Scope& scope = datum.Get<Scope>(i);
						scope.m_Parent = this;
					}
				}
			}

			if (m_Parent != nullptr)
			{
				auto [parentDatum, index] = m_Parent->FindContainedScope(toMove);
				parentDatum->Set(*this, index);
				toMove.m_Parent = nullptr;
			}
		}

		return *this;
	}

	Datum& Scope::operator[](KeyType key)
	{
		return Append(key);
	}

	Datum& Scope::operator[](size_t index)
	{
		return m_Order[index]->second;
	}

	bool Scope::operator==(const Scope& toCompare)
	{
		return Equals(&toCompare);
	}

	bool Scope::operator!=(const Scope& toCompare)
	{
		return !(operator==(toCompare));
	}

	bool Scope::Equals(const RTTI* rhs) const
	{
		const Scope* toCompare = rhs->As<Scope>();

		if (toCompare == nullptr)
		{
			return false;
		}

		bool isEqual = false;

		if (Size() == 0 && toCompare->Size() == 0)
		{
			isEqual = true;
		}
		else if (Size() == toCompare->Size())
		{
			for (auto it = m_Map.begin(); it != m_Map.end(); ++it)
			{
				const Datum* compareDatum = toCompare->Find(it->first);

				if (it->first != "this")
				{
					if (compareDatum != nullptr)
					{
						isEqual = *compareDatum == it->second;
						if (!isEqual)
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
			}
		}

		return isEqual;
	}

	Scope* Scope::Clone()
	{
		return new Scope(*this);
	}

	Datum& Scope::Append(KeyType& key)
	{
		EmptyStringCheck(key);

		auto [it, inserted] = m_Map.Insert(make_pair(key, Datum()));

		if (inserted)
		{
			m_Order.PushBack(&(*it));
		}

		return it->second;
	}

	Scope& Scope::AppendScope(KeyType& key)
	{
		EmptyStringCheck(key);

		Datum& datum = Append(key);
		
		if (datum.Type() != Datum::DatumTypes::TABLE && datum.Type() != Datum::DatumTypes::UNKNOWN)
		{
			throw std::runtime_error("Datum at this key is not of type table");
		}
		
		Scope* scope = new Scope();
		scope->m_Parent = this;
		datum.PushBack(*scope);
		return *scope;
	}

	void Scope::Adopt(Scope& toAdopt, KeyType& key)
	{
		EmptyStringCheck(key);

		if (IsDescendantOf(toAdopt))
		{
			throw std::runtime_error("Cannot adopt your anscestor");
		}

		if (&toAdopt == this)
		{
			throw std::runtime_error("Cannot adopt yourself");
		}

		Datum& datum = Append(key);

		if (datum.Type() != Datum::DatumTypes::TABLE && datum.Type() != Datum::DatumTypes::UNKNOWN)
		{
			throw std::runtime_error("Datum at this key is not of type table");
		}

		toAdopt.Orphan();
		toAdopt.m_Parent = this;
		datum.PushBack(toAdopt);
	}

	void Scope::Orphan()
	{
		if (m_Parent != nullptr)
		{
			auto [datum, index] = m_Parent->FindContainedScope(*this);

			datum->RemoveAt(index);

			m_Parent = nullptr;
		}
	}

	size_t Scope::Size() const
	{
		return m_Order.Size();
	}

	const Datum* Scope::Find(KeyType& key) const 
	{
		auto it = m_Map.Find(key);
		if (it == m_Map.end())
		{
			return nullptr;
		}

		return &(it->second);
	}

	Datum* Scope::Find(KeyType& key)
	{
		auto it = m_Map.Find(key);
		if (it == m_Map.end())
		{
			return nullptr;
		}

		return &(it->second);
	}

	std::pair<Datum*, size_t> Scope::FindContainedScope(Scope& toFind)
	{
		for (auto it = m_Map.begin(); it != m_Map.end(); ++it)
		{
			Datum& currentDatum = it->second;
			if (currentDatum.Type() == Datum::DatumTypes::TABLE)
			{
				size_t index = 0; 

				for (index; index < currentDatum.Size(); ++index)
				{
					if (&(currentDatum.Get<Scope>(index)) == &toFind)
					{
						break;
					}
				}

				if (index != currentDatum.Size())
				{
					return make_pair(&currentDatum, index);
				}
			}
		}

		return make_pair(nullptr, 0);
	}

	std::pair<Datum*, Scope*> Scope::Search(KeyType& key)
	{
		Datum* datum = Find(key);
		Scope* scope = this;

		if (datum == nullptr && m_Parent != nullptr)
		{
			std::tie(datum, scope) = m_Parent->Search(key);
		}
		else if (datum == nullptr && m_Parent == nullptr)
		{
			scope = nullptr;
		}

		return make_pair(datum, scope);
	}

	Scope* Scope::GetParent()
	{
		return m_Parent;
	}

	void Scope::EmptyStringCheck(KeyType& key)
	{
		if (key.empty())
		{
			throw std::runtime_error("Key cannot be empty");
		}
	}

	bool Scope::IsDescendantOf(Scope& toCheck)
	{
		if (&toCheck == m_Parent)
		{
			return true;
		}

		if (m_Parent != nullptr)
		{
			return m_Parent->IsDescendantOf(toCheck);
		}

		return false;
	}

	void Scope::Clear()
	{
		Orphan();
		for (auto it = m_Order.begin(); it != m_Order.end(); ++it)
		{
			Datum datum = (*it)->second;
			if (datum.Type() == Datum::DatumTypes::TABLE)
			{
				for (size_t i = 0; i < datum.Size(); ++i)
				{
					Scope* toDelete = &(datum.Get<Scope>(i));
					delete toDelete;
				}
			}
		}

		m_Map.Clear();
		m_Order.Clear();
	}

	Scope::~Scope()
	{
		Clear();
	}
}