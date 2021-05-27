#include "pch.h"
#include "ReactionAttributed.h"
#include "Event.h"
#include "EventMessageAttributed.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ReactionAttributed);
	
	ReactionAttributed::ReactionAttributed() : Reaction(TypeIdInstance()) 
	{
		Event<EventMessageAttributed>::Subscribe(*this);
	}

	const Vector<Signature> ReactionAttributed::Signatures()
	{
		return Vector<Signature>
		({
			Signature("m_Name", Datum::DatumTypes::STRING, 1, offsetof(ReactionAttributed, m_Name)),
			Signature("m_Subtype", Datum::DatumTypes::STRING, 1, offsetof(ReactionAttributed, m_Subtype)),
			Signature("m_Actions", Datum::DatumTypes::TABLE, 0, 0)
		});
	}

	ReactionAttributed* ReactionAttributed::Clone()
	{
		return new ReactionAttributed(*this);
	}

	const std::string& ReactionAttributed::GetSubtype() const
	{
		return m_Subtype;
	}

	void ReactionAttributed::SetSubtype(const std::string& subtype)
	{
		m_Subtype = subtype;
	}

	void ReactionAttributed::Notify(const EventPublisher& eventPub)
	{
		const Event<EventMessageAttributed>* event = eventPub.As<Event<EventMessageAttributed>>();

		if (event == nullptr)
		{
			throw std::runtime_error("Event must be of type EventMessageAttributed");
		}

		const EventMessageAttributed& message = event->Message();

		assert(message.GetWorldState() != nullptr);

		Datum* subtypeDatum = Find(m_SubtypeKey);
		bool subtypeMatch = false;

		for (size_t i = 0; i < subtypeDatum->Size(); ++i)
		{
			if (subtypeDatum->Get<std::string>(i) == message.GetSubtype())
			{
				subtypeMatch = true;
				break;
			}
		}

		if (subtypeMatch)
		{
			for (auto& pair : message.AuxiliaryAttributes())
			{
				Datum& datum = AppendAuxiliaryAttribute(pair->first);
				datum = pair->second;
			}

			ActionList::Update(*message.GetWorldState());
		}
	}

	ReactionAttributed::~ReactionAttributed()
	{
		Event<EventMessageAttributed>::Unsubscribe(*this);
	}
}