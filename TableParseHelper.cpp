#include "pch.h"
#include "TableParseHelper.h"
#include <cassert>
#include "Factory.h"

namespace FieaGameEngine
{
#pragma region Shared Data

	RTTI_DEFINITIONS(TableParseHelper::SharedData);

	TableParseHelper::SharedData::SharedData(Scope& root) : m_RootScope(&root) {};

	void TableParseHelper::SharedData::Initialize()
	{
		JsonParseCoordinator::SharedData::Initialize();
		m_RootScope->Clear();
	}

	TableParseHelper::SharedData* TableParseHelper::SharedData::Create() const
	{
		return new SharedData();
	}

#pragma endregion Shared Data

#pragma region Table Parse Helper

	RTTI_DEFINITIONS(TableParseHelper);

	IJsonParseHelper* TableParseHelper::Create() const
	{
		return new TableParseHelper();
	}

	void TableParseHelper::Initialize()
	{
		IJsonParseHelper::Initialize();
		m_Stack.Clear();
	}

	bool TableParseHelper::StartHandler(JsonParseCoordinator::SharedData& data, const std::string& key, const Json::Value& value, bool isArray)
	{
		UNREFERENCED_LOCAL(isArray);
		TableParseHelper::SharedData* customSharedData = data.As<TableParseHelper::SharedData>();
		
		if (customSharedData == nullptr)
		{
			return false;
		}

		if (customSharedData->m_RootScope == nullptr)
		{
			throw std::runtime_error("Root scope is null");
		}

		if (key == "type")
		{
			m_Stack.Top().m_CurrentDatum->SetType(Datum::m_TypeMap.at(value.asString()));
		}
		else if (key == "class")
		{
			assert(value.isString());

			m_Stack.Top().m_CurrentClass = value.asString();
		}
		else if (key == "value")
		{
			StackFrame& top = m_Stack.Top();
			if (top.m_CurrentDatum->Type() != Datum::DatumTypes::TABLE)
			{
				SetFunctions setFunc = m_SetFunctions[static_cast<int>(top.m_CurrentDatum->Type())];
				(this->*setFunc)(value);
			}
			else
			{
				Scope* scope = Factory<Scope>::Create(top.m_CurrentClass);

				if (scope == nullptr)
				{
					throw std::runtime_error("Appropriate factory was not found");
				}

				top.m_CurrentScope->Adopt(*scope, top.m_CurrentKey);

				m_Stack.Push(StackFrame(*scope, top.m_CurrentDatum, top.m_CurrentClass, key));
			}
		}
		else
		{
			if ((value.size() != 2) && (value.size() != 3))
			{
				return false;
			}

			if (!value.isMember("type") || !value.isMember("value"))
			{
				return false;
			}

			Scope* context = m_Stack.IsEmpty() ? customSharedData->m_RootScope : m_Stack.Top().m_CurrentScope;
			m_Stack.Push(StackFrame(*context, nullptr, "Scope", key));

			m_Stack.Top().m_CurrentDatum  = &(m_Stack.Top().m_CurrentScope->Append(key));
		}

		return true;
	}

	bool TableParseHelper::EndHandler(JsonParseCoordinator::SharedData& data, const std::string& key)
	{
		assert(data.Is(TableParseHelper::SharedData::TypeIdClass()));

#if defined(NDEBUG)
		UNREFERENCED_LOCAL(data);
#endif
		if (&(m_Stack.Top().m_CurrentKey) == &key)
		{
			m_Stack.Pop();
		}
		return true;
	}
	

#pragma endregion Table Parse Helper

#pragma region Push Back Functions

	void TableParseHelper::SetInt(const Json::Value& toPush)
	{
		if (m_Stack.Top().m_CurrentDatum->IsExternal())
		{
			m_Stack.Top().m_CurrentDatum->Set(toPush.asInt());
		}
		else
		{
			m_Stack.Top().m_CurrentDatum->PushBack(toPush.asInt());
		}
	}

	void TableParseHelper::SetFloat(const Json::Value& toPush)
	{
		if (m_Stack.Top().m_CurrentDatum->IsExternal())
		{
			m_Stack.Top().m_CurrentDatum->Set(toPush.asFloat());
		}
		else
		{
			m_Stack.Top().m_CurrentDatum->PushBack(toPush.asFloat());
		}
	}

	void TableParseHelper::SetString(const Json::Value& toPush)
	{
		if (m_Stack.Top().m_CurrentDatum->IsExternal())
		{
			m_Stack.Top().m_CurrentDatum->Set(toPush.asString());
		}
		else
		{
			m_Stack.Top().m_CurrentDatum->PushBack(toPush.asString());
		}
	}

	void TableParseHelper::SetVector(const Json::Value& toPush)
	{
		if (m_Stack.Top().m_CurrentDatum->IsExternal())
		{
			m_Stack.Top().m_CurrentDatum->SetFromString<glm::vec4>(toPush.asString());
		}
		else
		{
			m_Stack.Top().m_CurrentDatum->PushBackFromString<glm::vec4>(toPush.asString());
		}
	}

	void TableParseHelper::SetMatrix(const Json::Value& toPush)
	{
		if (m_Stack.Top().m_CurrentDatum->IsExternal())
		{
			m_Stack.Top().m_CurrentDatum->SetFromString<glm::mat4>(toPush.asString());
		}
		else
		{
			m_Stack.Top().m_CurrentDatum->PushBackFromString<glm::mat4>(toPush.asString());
		}
	}

#pragma endregion Push Back Functions

	TableParseHelper::StackFrame::StackFrame(Scope& scope, Datum* datum, std::string attributeClass, const std::string& key)
		: m_CurrentScope(&scope), m_CurrentDatum(datum), m_CurrentClass(attributeClass), m_CurrentKey(key) {}
}