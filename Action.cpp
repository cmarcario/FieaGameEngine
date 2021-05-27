#include "pch.h"
#include "Action.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Action);

	Action::Action(RTTI::IdType id) : Attributed(id) {}

	std::string Action::Name() const
	{
		return m_Name;
	}

	void Action::SetName(const std::string& name)
	{
		m_Name = name;
	}
}