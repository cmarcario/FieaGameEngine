#include "pch.h"
#include "World.h"
#include "Sector.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(World);

	World::World() : Attributed(World::TypeIdInstance()) {}

	World* World::Clone()
	{
		return new World(*this);
	}

	const Vector<Signature> World::Signatures()
	{
		return Vector<Signature>
		({
			Signature("m_Name", Datum::DatumTypes::STRING, 1, offsetof(World, m_Name)),
			Signature("m_Sectors", Datum::DatumTypes::TABLE, 0, 0)
		});
	}

	std::string World::Name() const
	{
		return m_Name;
	}

	void World::SetName(const std::string& name)
	{
		m_Name = name;
	}

	Datum& World::Sectors()
	{
		return *Find("m_Sectors");
	}

	Sector* World::CreateSector()
	{
		Sector* sector = new Sector();
		Adopt(*sector, "m_Sectors");

		return sector;
	}

	void World::Update(WorldState& worldState)
	{
		worldState.m_CurrentWorld = this;
		Datum& sectors = Sectors();

		for (size_t i = 0; i < sectors.Size(); ++i)
		{
			Sector* sector = static_cast<Sector*>(&(sectors.Get<Scope>(i)));
			sector->Update(worldState);
		}

		worldState.CreateActions();
		worldState.m_CurrentWorld = nullptr;
	}
}
