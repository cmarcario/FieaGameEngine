#include "pch.h"
#include "JsonParseCoordinator.h"
#include "IJsonParseHelper.h"
#include <fstream>
#include <limits>

namespace FieaGameEngine
{

#pragma region SharedData
	RTTI_DEFINITIONS(JsonParseCoordinator::SharedData);
	void JsonParseCoordinator::SharedData::Initialize() 
	{
		m_NestingDepth = 0;
	}

	JsonParseCoordinator* JsonParseCoordinator::SharedData::GetJsonParseCoordinator()
	{
		return m_ParseCoordinator;
	}

	const JsonParseCoordinator* JsonParseCoordinator::SharedData::GetJsonParseCoordinator() const
	{
		return m_ParseCoordinator;
	}

	void JsonParseCoordinator::SharedData::SetJsonParseCoordinator(JsonParseCoordinator* toSet)
	{
		m_ParseCoordinator = toSet;
	}

	void JsonParseCoordinator::SharedData::IncrementDepth()
	{
		++m_NestingDepth;
	}

	void JsonParseCoordinator::SharedData::DecrementDepth()
	{
		if (m_NestingDepth == 0)
		{
			throw std::runtime_error("depth is zero, cannot decrement further");
		}

		--m_NestingDepth;
	}

	size_t JsonParseCoordinator::SharedData::Depth()
	{
		if (m_NestingDepth == std::numeric_limits<size_t>::max())
		{
			throw std::runtime_error("depth is max, cannot increment further");
		}

		return m_NestingDepth;
	}
	

#pragma endregion SharedData

#pragma region JsonParseCoodinator

	RTTI_DEFINITIONS(JsonParseCoordinator);

	JsonParseCoordinator::JsonParseCoordinator(SharedData& data) : m_SharedData(&data) 
	{
		m_SharedData->SetJsonParseCoordinator(this);
	}

	JsonParseCoordinator::JsonParseCoordinator(JsonParseCoordinator&& toMove) noexcept
		: m_Helpers(std::move(toMove.m_Helpers)), m_SharedData(toMove.m_SharedData), m_IsClone(toMove.m_IsClone)
	{
		toMove.m_SharedData = nullptr;
		toMove.m_IsClone = false;
	}

	JsonParseCoordinator& JsonParseCoordinator::operator=(JsonParseCoordinator&& toMove) noexcept
	{
		if (&toMove != this)
		{
			m_Helpers = std::move(toMove.m_Helpers);

			m_SharedData = toMove.m_SharedData;
			toMove.m_SharedData = nullptr;
			toMove.m_IsClone = false;
		}

		return *this;
	}

	JsonParseCoordinator* JsonParseCoordinator::Clone() const
	{
		SharedData* clonedData = m_SharedData->Create();
		JsonParseCoordinator* clonedCoordinator = new JsonParseCoordinator(*clonedData);

		for (IJsonParseHelper* helper : m_Helpers)
		{
			clonedCoordinator->AddHelper(*(helper->Create()));
		}

		clonedCoordinator->m_IsClone = true;

		return clonedCoordinator;
	}

	const Vector<IJsonParseHelper*>& JsonParseCoordinator::Helpers() const 
	{
		return m_Helpers;
	}

	JsonParseCoordinator::SharedData& JsonParseCoordinator::GetSharedData()
	{
		if (m_SharedData == nullptr)
		{
			throw std::runtime_error("Shared Data is null");
		}

		return *m_SharedData;
	}
	
	const JsonParseCoordinator::SharedData& JsonParseCoordinator::GetSharedData() const
	{
		if (m_SharedData == nullptr)
		{
			throw std::runtime_error("Shared Data is null");
		}

		return *m_SharedData;
	}

	void JsonParseCoordinator::SetSharedData(SharedData& toSet)
	{
		m_SharedData = &toSet;
		toSet.SetJsonParseCoordinator(this);
	}

	void JsonParseCoordinator::AddHelper(IJsonParseHelper& helper)
	{
		if (m_IsClone)
		{
			throw std::runtime_error("Coordinator is a clone, cannot add helpers");
		}

		m_Helpers.PushBack(&helper);
	}

	void JsonParseCoordinator::RemoveHelper(IJsonParseHelper& helper)
	{
		if (m_IsClone)
		{
			throw std::runtime_error("Coordinator is a clone, cannot remove helpers");
		}

		m_Helpers.Remove(&helper);
	}

	bool JsonParseCoordinator::IsClone() const
	{
		return m_IsClone;
	}

	void JsonParseCoordinator::ParseFromFile(const std::string& fileName)
	{
		std::ifstream file(fileName, std::ifstream::binary);
		Json::Value root;
		file >> root;

		ParseMembers(root);
	}

	void JsonParseCoordinator::Parse(std::istream& stream)
	{
		Json::Value root;
		stream >> root;

		ParseMembers(root);
	}

	void JsonParseCoordinator::Parse(const std::string& jsonString)
	{
		std::istringstream inputStream(jsonString);
		Parse(inputStream);
	}

	void JsonParseCoordinator::Parse(const std::string& key, const Json::Value& value)
	{
		if (value.isObject())
		{
			m_SharedData->IncrementDepth();
			for (IJsonParseHelper* helper : m_Helpers)
			{
				if (helper->StartHandler(*m_SharedData, key, value, false))
				{
					ParseMembers(value);
					helper->EndHandler(*m_SharedData, key);
					break;
				}
			}
			m_SharedData->DecrementDepth();
		}

		else if (value.isArray())
		{
			for (Json::Value element : value)
			{
				if (element.isObject())
				{
					m_SharedData->IncrementDepth();
					ParseMembers(element);
					m_SharedData->DecrementDepth();
				}
				else
				{
					Parse(key, element);
				}
			}
		}

		else
		{
			for (IJsonParseHelper* helper : m_Helpers)
			{
				if (helper->StartHandler(*m_SharedData, key, value, false))
				{
					helper->EndHandler(*m_SharedData, key);
					break;
				}
			}
		}
	}

	void JsonParseCoordinator::ParseMembers(const Json::Value& root)
	{
		if (root.size() == 0)
		{
			throw std::runtime_error("Cannot parse empty value");
		}

		std::vector<std::string> keys = root.getMemberNames();
		for (std::string& key : keys)
		{
			Parse(key, root[key]);
		}
	}

	void JsonParseCoordinator::DeleteHelpers()
	{
		for (IJsonParseHelper* helper : m_Helpers)
		{
			delete helper;
		}
	}

	JsonParseCoordinator::~JsonParseCoordinator()
	{
		if (m_IsClone)
		{
			DeleteHelpers();

			delete m_SharedData;
		}
	}

#pragma endregion JsonParseCoordinator
}