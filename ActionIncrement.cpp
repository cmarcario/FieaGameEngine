#include "pch.h"
#include "ActionIncrement.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionIncrement);

	ActionIncrement::ActionIncrement() : Action(TypeIdInstance()) {};

	const Vector<Signature> ActionIncrement::Signatures()
	{
		return Vector<Signature>
			({
				Signature("m_Name", Datum::DatumTypes::STRING, 1, offsetof(ActionIncrement, m_Name)),
				Signature("m_Target", Datum::DatumTypes::STRING, 1, offsetof(ActionIncrement, m_Target)),
				Signature("m_Step", Datum::DatumTypes::FLOAT, 1, offsetof(ActionIncrement, m_Step)),
			});
	}

	ActionIncrement* ActionIncrement::Clone()
	{
		return new ActionIncrement(*this);
	}

	const std::string& ActionIncrement::Target() const
	{
		return m_Target;
	}

	void ActionIncrement::SetTarget(const std::string& target)
	{
		m_Target = target;
	}

	float ActionIncrement::Step() const
	{
		return m_Step;
	}

	void ActionIncrement::SetStep(float step)
	{
		m_Step = step;
	}

	void ActionIncrement::Update(WorldState& worldState)
	{
		worldState.m_CurrentAction = this;

		IncrementTarget();

		worldState.m_CurrentAction = nullptr;
	}

	void ActionIncrement::IncrementTarget()
	{
		auto [targetDatum, targetScope] = Search(m_Target);

		if (targetScope == nullptr)
		{
			throw runtime_error("target not found");
		}

		*targetDatum = targetDatum->Get<float>() + m_Step;
	}
}