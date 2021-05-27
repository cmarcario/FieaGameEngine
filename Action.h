#pragma once
#include "Attributed.h"
#include "WorldState.h"
#include <string>

namespace FieaGameEngine
{
	/// <summary>
	/// Action Class
	/// abstract class that holds the data for a single action
	/// </summary>
	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed)
	public:

		/// <summary>
		/// action default copy constructor
		/// </summary>
		Action(const Action&) = default;

		/// <summary>
		/// action default move constructor
		/// </summary>
		Action(Action&&) = default;

		/// <summary>
		/// action default destructor
		/// </summary>
		~Action() = default;

		/// <summary>
		/// action default copy assignment operator
		/// </summary>
		Action& operator=(const Action&) = default;

		/// <summary>
		/// action default move assignment operator
		/// </summary>
		Action& operator=(Action&&) = default;

		/// <summary>
		/// pure virtual update method
		/// </summary>
		/// <param name="worldState">the world state to be updated with</param>
		virtual void Update(WorldState& worldState) = 0;

		/// <summary>
		/// returns the name of the action
		/// </summary>
		/// <returns>the name of the entity</returns>
		std::string Name() const;

		/// <summary>
		/// sets the name of the action
		/// </summary>
		/// <param name="name">the name of the action</param>
		void SetName(const std::string& name);

	protected:
		/// <summary>
		/// protected action constructor
		/// populates scope based on passed in id types signatures
		/// </summary>
		/// <param name="id">the id to populate with</param>
		Action(RTTI::IdType id);

		/// <summary>
		/// the name of the action
		/// </summary>
		std::string m_Name;
	};
}

