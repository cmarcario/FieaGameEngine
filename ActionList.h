#pragma once
#include "Action.h"
#include "Signature.h"
#include "Factory.h"

namespace FieaGameEngine
{
	/// <summary>
	/// ActionList class
	/// stores a list of actions and updates them according
	/// </summary>
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action);
	public:
		/// <summary>
		/// action list constructor
		/// populates signatures based on rtti id
		/// </summary>
		/// <param name="id">the id to be populated with </param>
		ActionList(RTTI::IdType id);

		ActionList();

		/// <summary>
		/// default actionlist copy constructor
		/// </summary>
		ActionList(const ActionList&) = default;

		/// <summary>
		/// default actionlist move constructor
		/// </summary>
		ActionList(ActionList&&) = default;

		/// <summary>
		/// default actionlist destructor
		/// </summary>
		~ActionList() = default;

		/// <summary>
		/// default actionlist copy assignment operator
		/// </summary>
		ActionList& operator=(const ActionList&) = default;

		/// <summary>
		/// default actionlist move assignment operator
		/// </summary>
		ActionList& operator=(ActionList&&) = default;

		/// <summary>
		/// returns a heap allocated copy of itself
		/// </summary>
		/// <returns>a heap allocated copy of itself</returns>
		ActionList* Clone() override;

		/// <summary>
		/// returns the actions contained by this actionlist
		/// </summary>
		/// <returns>the actions contained by this actionlist</returns>
		Datum& Actions();

		/// <summary>
		/// iterates through its actions and updates them
		/// </summary>
		/// <param name="worldState">the worldstate to be updated with</param>
		void Update(WorldState& worldState) override;

		/// <summary>
		/// returns the signatures for actionlist
		/// </summary>
		/// <returns>the signatures for actionlist</returns>
		static const Vector<Signature> Signatures();
	};

	ConcreteFactory(ActionList, Scope);
}

