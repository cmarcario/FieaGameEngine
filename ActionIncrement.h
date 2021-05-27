#pragma once
#include "Action.h"
#include "Factory.h"
#include "Signature.h"

namespace FieaGameEngine
{
	/// <summary>
	/// ActionIncrement class
	/// increments a set target (float) by the step
	/// </summary>
	class ActionIncrement : public Action
	{
		RTTI_DECLARATIONS(ActionIncrement, Action);

	public:
		/// <summary>
		/// action increment constructor
		/// </summary>
		ActionIncrement();

		/// <summary>
		/// action increment default copy constructor
		/// </summary>
		ActionIncrement(const ActionIncrement&) = default;

		/// <summary>
		/// action increment default move constructor
		/// </summary>
		ActionIncrement(ActionIncrement&&) = default;

		/// <summary>
		/// actionIncrement default destructor
		/// </summary>
		~ActionIncrement() = default;

		/// <summary>
		/// returns the key of target to be incremented
		/// </summary>
		/// <returns>the key of target to be incremented</returns>
		const std::string& Target() const;

		/// <summary>
		/// sets the target to be incremented
		/// </summary>
		/// <param name="target">the key of the target to be incremented</param>
		void SetTarget(const std::string& target);

		/// <summary>
		/// returns the step to increment the target by
		/// </summary>
		/// <returns>the step to increment the target by</returns>
		float Step() const;

		/// <summary>
		/// sets the step to increment the target by
		/// </summary>
		/// <param name="step">the new step</param>
		void SetStep(float step);

		/// <summary>
		/// returns a heap allocated copy of itself
		/// </summary>
		/// <returns>a heap allocated copy of itself</returns>
		ActionIncrement* Clone() override;

		/// <summary>
		/// goes to the target and increments it by the step
		/// </summary>
		/// <param name="worldState">the worldstate to increment the target by</param>
		void Update(WorldState& worldState) override;

		/// <summary>
		/// signatures for actionincrement
		/// </summary>
		/// <returns>signatures for actionincrement</returns>
		static const Vector<Signature> Signatures();

	private:
		/// <summary>
		/// helper function that increments the target
		/// </summary>
		void IncrementTarget();

		/// <summary>
		/// the target to increment
		/// </summary>
		std::string m_Target;

		/// <summary>
		/// the step to increment the target by
		/// </summary>
		float m_Step = 1.0f;

	};

	ConcreteFactory(ActionIncrement, Scope);
}
