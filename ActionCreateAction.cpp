#include "pch.h"
#include "ActionCreateAction.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionCreateAction);

	ActionCreateAction::ActionCreateAction() : Action(TypeIdInstance()) {}

	const Vector<Signature> ActionCreateAction::Signatures()
	{
		return Vector<Signature>
			({
				Signature("m_Name", Datum::DatumTypes::STRING, 1, offsetof(ActionCreateAction, m_Name)),
				Signature("m_Prototype", Datum::DatumTypes::STRING, 1, offsetof(ActionCreateAction, m_Prototype)),
				Signature("m_ActionName", Datum::DatumTypes::STRING, 1, offsetof(ActionCreateAction, m_ActionName)),
			});
	}

	const std::string& ActionCreateAction::Prototype() const
	{
		return m_Prototype;
	}

	void ActionCreateAction::SetPrototype(const std::string& prototype)
	{
		m_Prototype = prototype;
	}

	const std::string& ActionCreateAction::ActionName() const
	{
		return m_ActionName;
	}

	void ActionCreateAction::SetActionName(const std::string& actionName)
	{
		m_ActionName = actionName;
	}

	ActionCreateAction* ActionCreateAction::Clone()
	{
		return new ActionCreateAction(*this);
	}

	void ActionCreateAction::Update(WorldState& worldState)
	{
		if (m_Parent == nullptr)
		{
			throw std::runtime_error("ActionCreateAction must have a parent");
		}

		worldState.m_CreateList.PushBack(WorldState::ActionInfo::ActionInfo(m_ActionName, m_Parent, m_Prototype));
	}
}
