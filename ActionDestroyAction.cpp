#include "pch.h"
#include "ActionDestroyAction.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionDestroyAction);

	ActionDestroyAction::ActionDestroyAction() : Action(TypeIdInstance()) {}

	const Vector<Signature> ActionDestroyAction::Signatures()
	{
		return Vector<Signature>
			({
				Signature("m_Name", Datum::DatumTypes::STRING, 1, offsetof(ActionDestroyAction, m_Name)),
				Signature("m_ActionName", Datum::DatumTypes::STRING, 1, offsetof(ActionDestroyAction, m_ActionName)),
			});
	}

	const std::string& ActionDestroyAction::ActionName() const
	{
		return m_ActionName;
	}

	void ActionDestroyAction::SetActionName(const std::string& actionName)
	{
		m_ActionName = actionName;
	}

	ActionDestroyAction* ActionDestroyAction::Clone()
	{
		return new ActionDestroyAction(*this);
	}

	void ActionDestroyAction::Update(WorldState& worldState)
	{
		if (m_Parent == nullptr)
		{
			throw std::runtime_error("ActionDestroyAction must have a parent");
		}

		worldState.m_DestroyList.PushBack(WorldState::ActionInfo::ActionInfo(m_ActionName, m_Parent));
	}
}

