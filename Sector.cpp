#include "pch.h"
#include "Sector.h"
#include "Entity.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Sector);

	Sector::Sector() : Attributed(Sector::TypeIdInstance()) 
	{
		m_World = static_cast<World*>(m_Parent);
	}

	Sector* Sector::Clone()
	{
		return new Sector(*this);
	}

	const Vector<Signature> Sector::Signatures()
	{
		return Vector<Signature>
		({
			Signature("m_Name", Datum::DatumTypes::STRING, 1, offsetof(Sector, m_Name)),
			Signature("m_World", Datum::DatumTypes::POINTER, 1, offsetof(Sector, m_World)),
			Signature("m_Entities", Datum::DatumTypes::TABLE, 0, 0)
		});
	}

	Datum& Sector::Entities()
	{
		return *Find("m_Entities");
	}

	Entity* Sector::CreateEntity()
	{
		Entity* entity = new Entity();
		Adopt(*entity, "m_Entities");

		return entity;
	}

	World* Sector::GetWorld() const
	{
		return m_World;
	}

	void Sector::SetWorld(World& toSet)
	{
		m_World = &toSet;
		m_World->Adopt(*this, "m_Sectors");
	}

	void Sector::Update(WorldState& worldState)
	{
		worldState.m_CurrentSector = this;
		Datum& entities = Entities();

		for (size_t i = 0; i < entities.Size(); ++i)
		{
			Entity* entitity = static_cast<Entity*>(&(entities.Get<Scope>(i)));
			entitity->Update(worldState);
		}
		worldState.m_CurrentSector = nullptr;
	}

	std::string Sector::Name() const
	{
		return m_Name;
	}

	void Sector::SetName(const std::string& name)
	{
		m_Name = name;
	}
}