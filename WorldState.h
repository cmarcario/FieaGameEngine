#pragma once
#include "GameTime.h"
#include "Stack.h"
#include <string>
#include "Scope.h"

namespace FieaGameEngine
{
	class World; 
	class Sector; 
	class Entity;
	class Action;

	/// <summary>
	/// keeps track of the current state of the world
	/// </summary>
	class WorldState
	{
	public:

		/// <summary>
		/// stores the info needed to create / destoy actions
		/// </summary>
		struct ActionInfo
		{
			/// <summary>
			/// the name of the prototype to be created
			/// </summary>
			std::string m_Prototype;

			/// <summary>
			/// the name to be given to the action
			/// </summary>
			std::string m_ActionName;

			/// <summary>
			/// the scope whos actions it should be put into / the search it should start with
			/// </summary>
			Scope* m_Context;

			/// <summary>
			/// constructor for action info
			/// </summary>
			/// <param name="actionName">the name of the action</param>
			/// <param name="context">the context the action is in</param>
			/// <param name="prototype">the name of the actions class</param>
			ActionInfo(const std::string& actionName, Scope* context, const std::string& prototype = "" );
		};
		/// <summary>
		/// iterates through the list of actions to be created and creates them in the proper context
		/// empties the list when done
		/// </summary>
		void CreateActions();

		/// <summary>
		/// iterates through the list of actions to be destroyed and destroys them
		/// clears the list when done
		/// </summary>
		void DestroyActions();

		/// <summary>
		/// the world being processed
		/// </summary>
		World* m_CurrentWorld = nullptr;

		/// <summary>
		/// the sector being processed
		/// </summary>
		Sector* m_CurrentSector = nullptr;

		/// <summary>
		/// the entity being processed
		/// </summary>
		Entity* m_CurrentEntity = nullptr;

		/// <summary>
		/// the action being processed
		/// </summary>
		Action* m_CurrentAction = nullptr;

		/// <summary>
		/// list of actions to be created at the end of an update
		/// </summary>
		SList<ActionInfo> m_CreateList;

		/// <summary>
		/// list of actions to be destroyed at the end of an update
		/// </summary>
		SList<ActionInfo> m_DestroyList;
	};
}

