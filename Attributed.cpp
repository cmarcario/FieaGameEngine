#include "pch.h"
#include "Attributed.h"
#include "TypeManager.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Attributed);

	Attributed::Attributed(RTTI::IdType id)
	{
		(*this)["this"] = this;
		Populate(id);
	}

	Attributed::Attributed(const Attributed& toCopy) : Scope(toCopy)
	{
		UpdatePointers(toCopy);
	}

	Attributed::Attributed(Attributed&& toMove) noexcept : Scope(std::move(toMove))
	{
		UpdatePointers(toMove);
	}

	Attributed& Attributed::operator=(const Attributed& toCopy)
	{
		if (this != &toCopy)
		{
			Clear();
			Scope::operator=(toCopy);
			UpdatePointers(toCopy);
		}
		return *this;
	}

	Attributed& Attributed::operator=(Attributed&& toMove) noexcept
	{
		if (this != &toMove)
		{
			Clear();
			Scope::operator=(std::move(toMove));
			UpdatePointers(toMove);
		}
		return *this;
	}

	void Attributed::Populate(RTTI::IdType id)
	{
		Vector<Signature> signatures = TypeManager::GetSignatures(id);

		for (const Signature& signature : signatures)
		{
			assert(signature.m_Type != Datum::DatumTypes::UNKNOWN);

			Datum& datum = Append(signature.m_Name);

			if (signature.m_Type == Datum::DatumTypes::TABLE)
			{
				datum.SetType(Datum::DatumTypes::TABLE);
				datum.Reserve(signature.m_Size);
				for (size_t i = 0; i < signature.m_Size; ++i)
				{
					AppendScope(signature.m_Name);
				}
			}
			else
			{
				void* data = reinterpret_cast<std::uint8_t*>(this) + signature.m_Offset;
				datum.SetStorage(data, signature.m_Size, signature.m_Type);
			}
		}
	}

	bool Attributed::IsAttribute(KeyType& key)
	{
		return (Find(key) != nullptr);
	}

	bool Attributed::IsPrescribedAttribute(KeyType& key)
	{
		if (key == "this")
		{
			return true;
		}

		for (Signature& signature : TypeManager::GetSignatures(TypeIdInstance()))
		{
			if (key == signature.m_Name)
			{
				return true;
			}
		}

		return false;
	}

	bool Attributed::IsAuxiliaryAttribute(KeyType& key)
	{
		return (IsAttribute(key) && !IsPrescribedAttribute(key));
	}

	Datum& Attributed::AppendAuxiliaryAttribute(KeyType& key)
	{
		if (IsPrescribedAttribute(key))
		{
			throw std::runtime_error("Key is prescribed");
		}

		return Append(key);
	}

	const Vector<Attributed::MapPairType*>& Attributed::Attributes()
	{
		return m_Order;
	}

	const Vector<Attributed::MapPairType*> Attributed::PrescribedAttributes()
	{
		Vector<Signature> signatures = TypeManager::GetSignatures(TypeIdInstance());
		Vector<MapPairType*> vector;
		
		for (size_t i = 0; i < (signatures.Size() + 1); ++i)
		{
			vector.PushBack(m_Order[i]);
		}

		return vector;
	}

	const Vector<Attributed::MapPairType*> Attributed::AuxiliaryAttributes() const
	{
		Vector<Signature> signatures = TypeManager::GetSignatures(TypeIdInstance());
		Vector<MapPairType*> vector;

		for (size_t i = (signatures.Size() + 1); i < m_Order.Size(); ++i)
		{
			vector.PushBack(m_Order[i]);
		}

		return vector;
	}



	void Attributed::UpdatePointers(const Attributed& other)
	{
		(*this)["this"] = this;
		Vector<Signature> signatures = TypeManager::GetSignatures(other.TypeIdInstance());

		for (const Signature& signature : signatures)
		{
			if (signature.m_Type != Datum::DatumTypes::TABLE)
			{
				Datum* datum = Find(signature.m_Name);
				void* data = reinterpret_cast<std::uint8_t*>(this) + signature.m_Offset;
				datum->SetStorage(data, signature.m_Size, signature.m_Type);
			}
		}
	}
}