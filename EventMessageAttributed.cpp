#include "pch.h"
#include "EventMessageAttributed.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(EventMessageAttributed);

	EventMessageAttributed::EventMessageAttributed() : Attributed(TypeIdInstance()) {};

	const Vector<Signature> EventMessageAttributed::Signatures()
	{
		return Vector<Signature>
			({
				Signature("m_Subtype", Datum::DatumTypes::STRING, 1, offsetof(EventMessageAttributed, m_Subtype)),
				Signature("m_WorldState", Datum::DatumTypes::POINTER, 1, offsetof(EventMessageAttributed, m_WorldState))
			});
	}

	EventMessageAttributed* EventMessageAttributed::Clone()
	{
		return new EventMessageAttributed(*this);
	}

	const std::string& EventMessageAttributed::GetSubtype() const
	{
		return m_Subtype;
	}

	void EventMessageAttributed::SetSubtype(const std::string& subtype)
	{
		m_Subtype = subtype;
	}

	WorldState* EventMessageAttributed::GetWorldState() const
	{
		return m_WorldState;
	}

	void EventMessageAttributed::SetWorldState(WorldState& worldState)
	{
		m_WorldState = &worldState;
	}

}
