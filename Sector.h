#pragma once
#include "Attributed.h"
#include "Factory.h"
#include "World.h"
#include <string>

namespace FieaGameEngine
{
	class Entity;
	class Sector : public Attributed
	{
		RTTI_DECLARATIONS(Sector, Attributed);
	public:
		/// <summary>
		/// Sector class
		/// contains the information for all its entities, and the general information for the sector
		/// </summary>
		explicit Sector();

		/// <summary>
		/// sector default copy constructor
		/// </summary>
		Sector(const Sector&) = default;

		/// <summary>
		/// sector default move constructor
		/// </summary>
		Sector(Sector&&) = default;

		/// <summary>
		/// sector default destuctor
		/// </summary>
		~Sector() = default;

		/// <summary>
		/// sector default copy assignment operator
		/// </summary>
		Sector& operator=(const Sector&) = default;

		/// <summary>
		/// sector default move assignment operator
		/// </summary>
		Sector& operator=(Sector&&) = default;

		/// <summary>
		/// creates a heap allocated copy of itself
		/// </summary>
		/// <returns>a pointer to the new sector</returns>
		Sector* Clone() override;

		/// <summary>
		/// calls update on all its entities
		/// </summary>
		/// <param name="worldState">the worldstate needed for the update</param>
		void Update(WorldState& worldState);

		/// <summary>
		/// gets the world that this sector is a part of
		/// </summary>
		/// <returns>the world that this sector is in</returns>
		World* GetWorld() const;

		/// <summary>
		/// sets the world that this sector is in
		/// orphans the sector and adopts it into the new world
		/// </summary>
		/// <param name="toSet">the world to be added into</param>
		void SetWorld(World& toSet);

		/// <summary>
		/// returns the name of the sector
		/// </summary>
		/// <returns>the name of the sector</returns>
		std::string Name() const;

		/// <summary>
		/// sets the name of the sector
		/// </summary>
		/// <param name="name">the name to be set</param>
		void SetName(const std::string& name);
		
		/// <summary>
		/// returns the datum containing this sectors entities
		/// </summary>
		/// <returns>the datum containing this sectors entities</returns>
		Datum& Entities();

		/// <summary>
		/// creates a new entity and adds it to this sector
		/// </summary>
		/// <returns>the address of the new entity</returns>
		Entity* CreateEntity();

		/// <summary>
		/// static array that returns the sectors signatures for the type manager
		/// </summary>
		/// <returns>the array of signatures</returns>
		static const Vector<Signature> Signatures();
	private:
		/// <summary>
		/// the name of the sector
		/// </summary>
		std::string m_Name;

		/// <summary>
		/// the world the sector belongs to
		/// </summary>
		World* m_World = nullptr;
	};

	ConcreteFactory(Sector, Scope);
}

