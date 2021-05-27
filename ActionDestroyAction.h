#pragma once
#include "Action.h"
#include "Signature.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Action
	/// queues an action to be destroyed at the end of the update loop
	/// </summary>
	class ActionDestroyAction : public Action
	{
		RTTI_DECLARATIONS(ActionDestroyAction, Action);
	public:
		/// <summary>
		/// ActionDestroyAction constructor
		/// populates based on its signatures
		/// </summary>
		ActionDestroyAction();

		/// <summary>
		/// ActionDestroyAction default copy constructor
		/// </summary>
		ActionDestroyAction(const ActionDestroyAction&) = default;

		/// <summary>
		/// ActionDestroyAction default move constructor
		/// </summary>
		ActionDestroyAction(ActionDestroyAction&&) = default;

		/// <summary>
		/// ActionDestroyAction default destructor
		/// </summary>
		~ActionDestroyAction() = default;

		/// <summary>
		/// ActionDestroyAction default copy assignment operator
		/// </summary>
		ActionDestroyAction& operator=(const ActionDestroyAction&) = default;

		/// <summary>
		/// ActionDestroyAction default move assignment operator
		/// </summary>
		ActionDestroyAction& operator=(ActionDestroyAction&&) = default;

		/// <summary>
		/// returns the name of the action to be destroyed
		/// </summary>
		/// <returns></returns>
		const std::string& ActionName() const;

		/// <summary>
		/// sets the name of the action to be destroyed
		/// </summary>
		/// <param name="actionName">the new name of the action to be destroyed</param>
		void SetActionName(const std::string & actionName);

		/// <summary>
		/// returns a heap allocated ccopy of itself
		/// </summary>
		/// <returns>a heap allocated copy of itself</returns>
		ActionDestroyAction* Clone() override;

		/// <summary>
		/// adds the name of the action and its parent to the queue of actions to be destroyed
		/// </summary>
		/// <param name="worldState">the worldstate being used for the update whos queue we are adding to</param>
		void Update(WorldState & worldState) override;

		/// <summary>
		/// signatures for actiondestroyaction
		/// </summary>
		/// <returns>the signatures for actiondestroyaction</returns>
		static const Vector<Signature> Signatures();

	private:
		/// <summary>
		/// the name of the action to be destroyed
		/// </summary>
		std::string m_ActionName;
	};
}

