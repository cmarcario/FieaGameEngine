#include "pch.h"
#include "ActionIf.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionIf);

	ActionIf::ActionIf() : Action(TypeIdInstance()) {};

	const Vector<Signature> ActionIf::Signatures()
	{
		return Vector<Signature>
			({
				Signature("m_Name", Datum::DatumTypes::STRING, 1, offsetof(ActionIf, m_Name)),
				Signature("m_Condition", Datum::DatumTypes::INTEGER, 1, offsetof(ActionIf, m_Condition)),
				Signature("m_Then", Datum::DatumTypes::TABLE, 0, 0),
				Signature("m_Else", Datum::DatumTypes::TABLE, 0, 0)
			});
	}

	ActionIf* ActionIf::Clone()
	{
		return new ActionIf(*this);
	}

	int ActionIf::Condition() const
	{
		return m_Condition;
	}

	void ActionIf::SetCondition(int condition)
	{
		m_Condition = condition;
	}

	void ActionIf::Update(WorldState& worldState)
	{
		worldState.m_CurrentAction = this;

		Datum* actions = nullptr;

		if (m_Condition)
		{
			actions = &(*Find("m_Then"));
		}
		else
		{
			actions = &(*Find("m_Else"));
		}

		for (size_t i = 0; i < actions->Size(); ++i)
		{
			Action* action = static_cast<Action*>(&(actions->Get<Scope>(i)));
			action->Update(worldState);
		}

	}

}