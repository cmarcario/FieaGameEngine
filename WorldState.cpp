#include "pch.h"
#include "Factory.h"
#include "Action.h"
#include "WorldState.h"

namespace FieaGameEngine
{
	void WorldState::CreateActions()
	{
		for (auto& action : m_CreateList)
		{
			assert(action.m_Context != nullptr);
			Scope* newAction = Factory<Scope>::Create(action.m_Prototype);

			if (newAction == nullptr)
			{
				throw std::runtime_error("Factory not found");
			}

			action.m_Context->Adopt(*newAction, "m_Actions");
			static_cast<Action*>(newAction)->SetName(action.m_ActionName);
		}

		m_CreateList.Clear();
	}

	void WorldState::DestroyActions()
	{
		for (auto& action : m_DestroyList)
		{
			Scope* currentScope = action.m_Context;
			bool destroyed = false;

			while (currentScope != nullptr && !destroyed)
			{
				Datum* actions = currentScope->Find("m_Actions");

				if (actions != nullptr)
				{
					for (size_t i = 0; i < actions->Size(); ++i)
					{
						Action* currentAction = static_cast<Action*>(&(actions->Get<Scope>(i)));

						if (currentAction->Name() == action.m_ActionName)
						{
							delete currentAction;
							actions->Remove(*currentAction);
							destroyed = true;
							break;
						}
					}
				}

				currentScope = currentScope->GetParent();
			}
		}

		m_DestroyList.Clear();
	}

	WorldState::ActionInfo::ActionInfo(const std::string& actionName, Scope* context, const std::string& prototype) :
		m_ActionName(actionName), m_Context(context), m_Prototype(prototype) {}
}
