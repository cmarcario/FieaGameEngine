#pragma once
#include "ActionList.h"
#include "EventSubscriber.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Reaction abstract class
	/// inherits from actionList and EventSubscriber
	/// </summary>
	class Reaction : public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList);

	public:
		/// <summary>
		/// Reaction pure virtual destructor
		/// </summary>
		virtual ~Reaction() = 0 {};

	protected:
		/// <summary>
		/// reaction constructor
		/// calls actionLists constructor with the passed in rtti id type
		/// </summary>
		/// <param name="id">the rtti id to pass on</param>
		Reaction(RTTI::IdType id);
	};
}