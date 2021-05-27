#pragma once
#include "Attributed.h"
#include "Factory.h"
#include <string>
#include "Signature.h"
#include "WorldState.h"


namespace FieaGameEngine
{
	class Sector;

	/// <summary>
	/// World class
	/// contains the information for all the sectors, and the general information for the world
	/// </summary>
	class World : public Attributed
	{
		RTTI_DECLARATIONS(World, Attributed);
	public:
		/// <summary>
		/// constructor for world
		/// calls the constructor for attributed 
		/// </summary>
		explicit World();

		/// <summary>
		/// default copy constructor for world
		/// </summary>
		World(const World&) = default;

		/// <summary>
		/// default move constructor for world
		/// </summary>
		World(World&&) = default;

		/// <summary>
		/// default destructor for world
		/// </summary>
		~World() = default;

		/// <summary>
		/// default copy assignment operator for world
		/// </summary>
		World& operator=(const World&) = default;

		/// <summary>
		/// default move assignment operator for world
		/// </summary>
		World& operator=(World&&) = default;

		/// <summary>
		/// creates a heap allocated copy of itself
		/// </summary>
		/// <returns>a pointer to the new world</returns>
		World* Clone() override;

		/// <summary>
		/// returns the name of the world
		/// </summary>
		/// <returns>the name of the world</returns>
		std::string Name() const;

		/// <summary>
		/// sets the name of the world
		/// </summary>
		/// <param name="name">the name to set</param>
		void SetName(const std::string& name);

		/// <summary>
		/// returns the sectors within the world
		/// </summary>
		/// <returns>the sectors that the world contains</returns>
		Datum& Sectors();

		/// <summary>
		/// creates a new sector and adds it to the sector datum
		/// </summary>
		/// <returns>the new sector</returns>
		Sector* CreateSector();

		/// <summary>
		/// calls update on all the sectors
		/// </summary>
		/// <param name="worldState">the worldstate needed for the update</param>
		void Update(WorldState& worldState);

		/// <summary>
		/// static array that returns the worlds signatures for the type manager
		/// </summary>
		/// <returns>the array of signatures</returns>
		static const Vector<Signature> Signatures();

	private:
		/// <summary>
		/// name of the world
		/// </summary>
		std::string m_Name;
	};
}