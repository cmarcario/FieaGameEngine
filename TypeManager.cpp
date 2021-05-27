#include "pch.h"
#include "TypeManager.h"

namespace FieaGameEngine
{
	HashMap<const RTTI::IdType, TypeManager::SignatureList> TypeManager::s_SignatureMap;

	void TypeManager::AddType(RTTI::IdType id, SignatureList signatures)
	{
		if (ContainsKey(id))
		{
			throw std::runtime_error("Type already registered");
		}

		s_SignatureMap.Insert(make_pair(id, std::move(signatures)));
	}

	void TypeManager::RemoveType(RTTI::IdType id)
	{
		s_SignatureMap.Remove(id);
	}

	TypeManager::SignatureList TypeManager::GetSignatures(RTTI::IdType id)
	{
		return s_SignatureMap.At(id);
	}

	size_t TypeManager::Size()
	{
		return s_SignatureMap.Size();
	}

	bool TypeManager::ContainsKey(RTTI::IdType id)
	{
		return s_SignatureMap.ContainsKey(id);
	}
	void TypeManager::Clear()
	{
		s_SignatureMap.Clear();
	}
}