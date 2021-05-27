#include "pch.h"
#include "ActionList.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionList);

	ActionList::ActionList(RTTI::IdType id) : Action(id) {}

	ActionList::ActionList() : Action(TypeIdInstance()) {}

	const Vector<Signature> ActionList::Signatures()
	{
		return Vector<Signature>
			({
				Signature("m_Name", Datum::DatumTypes::STRING, 1, offsetof(ActionList, m_Name)),
				Signature("m_Actions", Datum::DatumTypes::TABLE, 0, 0)
			});
	}

	ActionList* ActionList::Clone()
	{
		return new ActionList(*this);
	}

	Datum& ActionList::Actions()
	{
		return *Find("m_Actions");
	}

	void ActionList::Update(WorldState& worldState)
	{
		Datum& actions = Actions();

		for (size_t i = 0; i < actions.Size(); ++i)
		{
			Action* action = static_cast<Action*>(&(actions.Get<Scope>(i)));
			action->Update(worldState);
		}

		worldState.CreateActions();
		worldState.DestroyActions();
	}
}