#include "pch.h"
#include "Entity.h"
#include "Action.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Entity);

	Entity::Entity(RTTI::IdType id) : Attributed(id) 
	{
		m_Sector = static_cast<Sector*>(m_Parent);
	}

	Entity* Entity::Clone()
	{
		return new Entity(*this);
	}

	const Vector<Signature> Entity::Signatures()
	{
		return Vector<Signature>
		({
			Signature("m_Name", Datum::DatumTypes::STRING, 1, offsetof(Entity, m_Name)),
			Signature("m_Sector", Datum::DatumTypes::POINTER, 1, offsetof(Entity, m_Sector)),
			Signature("m_Actions", Datum::DatumTypes::TABLE, 0, 0)
		});
	}

	Sector* Entity::GetSector() const
	{
		return m_Sector;
	}

	void Entity::SetSector(Sector& toSet)
	{
		m_Sector = &toSet;
		m_Sector->Adopt(*this, "m_Entities");
	}

	void Entity::Update(WorldState& worldState)
	{
		worldState.m_CurrentEntity = this;
		
		Datum& actions = Actions();

		for (size_t i = 0; i < actions.Size(); ++i)
		{
			Action* action = static_cast<Action*>(&(actions.Get<Scope>(i)));
			action->Update(worldState);
		}

		worldState.m_CurrentEntity = nullptr;
	}

	std::string Entity::Name() const
	{
		return m_Name;
	}

	void Entity::SetName(const std::string& name)
	{
		m_Name = name;
	}

	Datum& Entity::Actions()
	{
		return *Find("m_Actions");
	}

	Scope* Entity::CreateAction(const std::string& actionName)
	{
		Scope* action = Factory<Scope>::Create(actionName);

		if (action == nullptr)
		{
			throw::std::runtime_error("Action name not found in factories");
		}

		Adopt(*action, "m_Actions");
		return action;
	}
}