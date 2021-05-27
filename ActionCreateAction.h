#pragma once
#include "Action.h"
#include "Factory.h"
#include "Signature.h"
#include <string>

namespace FieaGameEngine
{
	/// <summary>
	/// ActionCreateAction class
	/// adds a name, prototype name, and context to a queue of actions to be created
	/// </summary>
	class ActionCreateAction : public Action
	{
		RTTI_DECLARATIONS(ActionCreateAction, Action);
	public:
		/// <summary>
		/// actionCreateAction constructor
		/// populates based on its signatures
		/// </summary>
		ActionCreateAction();

		/// <summary>
		/// actionCreateAction default copy constructor
		/// </summary>
		ActionCreateAction(const ActionCreateAction&) = default;

		/// <summary>
		/// actionCreateAction default move constructor
		/// </summary>
		ActionCreateAction(ActionCreateAction&&) = default;

		/// <summary>
		/// actionCreateAction default destructor
		/// </summary>
		~ActionCreateAction() = default;

		/// <summary>
		/// actionCreateAction default copy assignment operator
		/// </summary>
		ActionCreateAction& operator=(const ActionCreateAction&) = default;

		/// <summary>
		/// actionCreateAction default move assignment operator
		/// </summary>
		ActionCreateAction& operator=(ActionCreateAction&&) = default;

		/// <summary>
		/// returns the name of the prototype that is to be created
		/// </summary>
		/// <returns>the name of the prototype that is to be created</returns>
		const std::string& Prototype() const;

		/// <summary>
		/// set a new prototype to be created
		/// </summary>
		/// <param name="prototype">the name of the new prototype</param>
		void SetPrototype(const std::string& prototype);

		/// <summary>
		/// returns the name to give a newly created action
		/// </summary>
		/// <returns>the name to give a newly created action</returns>
		const std::string& ActionName() const;

		/// <summary>
		/// sets the new name to give an action upon creation
		/// </summary>
		/// <param name="actionName">the new name to give an action upon creation</param>
		void SetActionName(const std::string& actionName);

		/// <summary>
		/// returns a heap allocated copy of itself
		/// </summary>
		/// <returns> a heap allocated copy of itself</returns>
		ActionCreateAction* Clone() override;

		/// <summary>
		/// adds the prototype, action name, and its parent to the queue of actions to be created
		/// </summary>
		/// <param name="worldState"></param>
		void Update(WorldState& worldState) override;

		/// <summary>
		/// attribute signatures for actionCreateAction
		/// </summary>
		/// <returns>signatures for actionCreateAction</returns>
		static const Vector<Signature> Signatures();

	private:
		/// <summary>
		/// the name of the prototype to be created
		/// </summary>
		std::string m_Prototype;

		/// <summary>
		/// the name to be given to the action when it is created
		/// </summary>
		std::string m_ActionName;
	};

	ConcreteFactory(ActionCreateAction, Scope);
}

