#pragma once
#include "Action.h"
#include "Factory.h"
#include "Signature.h"

namespace FieaGameEngine
{
	/// <summary>
	/// ActionIf class
	/// based on a condition, executes a series of actions upon update
	/// </summary>
	class ActionIf : public Action
	{
		RTTI_DECLARATIONS(ActionIf, Action);
	public:
		/// <summary>
		/// construtor for actionif
		/// populates based on its id type
		/// </summary>
		ActionIf();

		/// <summary>
		/// actionif default copy constructor
		/// </summary>
		ActionIf(const ActionIf&) = default;

		/// <summary>
		/// actionif default move constructor
		/// </summary>
		ActionIf(ActionIf&&) = default;

		/// <summary>
		/// actionif default destructor
		/// </summary>
		~ActionIf() = default;

		/// <summary>
		/// actionif default copy assignment
		/// </summary>
		ActionIf& operator=(const ActionIf&) = default;

		/// <summary>
		/// actionif default move assingment
		/// </summary>
		ActionIf& operator=(ActionIf&&) = default;

		/// <summary>
		/// returns the condition to act upon
		/// </summary>
		/// <returns>the condition to act upon</returns>
		int Condition() const;

		/// <summary>
		/// sets the condition to act upon
		/// </summary>
		/// <param name="condition">what to set the condition to</param>
		void SetCondition(int condition);
		
		/// <summary>
		/// looks to see what the condition is, and then updates the associated actions accordingly
		/// </summary>
		/// <param name="worldState"></param>
		void Update(WorldState& worldState) override;
		
		/// <summary>
		/// returns a heap allocated copy of itself
		/// </summary>
		/// <returns>a heap allocated copy of itself</returns>
		ActionIf* Clone() override;

		/// <summary>
		/// signatures for actionif attributes
		/// </summary>
		/// <returns></returns>
		static const Vector<Signature> Signatures();

	private:
		/// <summary>
		/// the condition to act upon
		/// </summary>
		int m_Condition = 0;
	};

	ConcreteFactory(ActionIf, Scope);
}
