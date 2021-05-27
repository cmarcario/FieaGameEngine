#pragma once
#include "Attributed.h"
#include "Sector.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class Entity : public Attributed
	{
		RTTI_DECLARATIONS(Entity, Attributed);
	public:
		/// <summary>
		/// Entity class
		/// contains information necessary for a game process/object
		/// </summary>
		Entity(RTTI::IdType id = TypeIdClass()); 
		
		/// <summary>
		/// entity default copy constructor
		/// </summary>
		Entity(const Entity&) = default;

		/// <summary>
		/// entity default move constructor
		/// </summary>
		Entity(Entity&&) = default;

		/// <summary>
		/// entity default destructor
		/// </summary>
		~Entity() = default;

		/// <summary>
		/// entity default copy assignment operator
		/// </summary>
		Entity& operator=(const Entity&) = default;

		/// <summary>
		/// entity default move assignmetn operator
		/// </summary>
		Entity& operator=(Entity&&) = default;

		/// <summary>
		/// creates a heap allocated copy of itself
		/// </summary>
		/// <returns>the new entity</returns>
		Entity* Clone() override;

		/// <summary>
		/// currently has no function, will update actions in the future
		/// </summary>
		/// <param name="worldState">the worldstate used for the update</param>
		void Update(WorldState & worldState);

		/// <summary>
		/// gets the sector that this entity belongs to
		/// </summary>
		/// <returns>the sector that this entity belongs to</returns>
		Sector* GetSector() const;

		/// <summary>
		/// adopts this entity into the one passed in
		/// </summary>
		/// <param name="toSet">the sector to be set to</param>
		void SetSector(Sector& toSet);

		/// <summary>
		/// returns the name of the entity
		/// </summary>
		/// <returns>the name of the entity</returns>
		std::string Name() const;

		/// <summary>
		/// sets the name of the entity
		/// </summary>
		/// <param name="name">the name of the entity</param>
		void SetName(const std::string & name);

		/// <summary>
		/// returns the list of actions associated with this entity
		/// </summary>
		/// <returns>the list of actions associated with this entity</returns>
		Datum& Actions();

		/// <summary>
		/// creates a new action and adds it to the table
		/// </summary>
		/// <param name="actionName">the action to create</param>
		/// <returns>the new action</returns>
		Scope* CreateAction(const std::string& actionName);

		/// <summary>
		/// static array that returns the worlds signatures for the type manager
		/// </summary>
		/// <returns>the array of signatures</returns>
		static const Vector<Signature> Signatures();
	protected:

		/// <summary>
		/// the name of the entity
		/// </summary>
		std::string m_Name;

		/// <summary>
		/// the sector that the entity belongs to
		/// </summary>
		Sector* m_Sector = nullptr;
	};

	ConcreteFactory(Entity, Scope);
}
