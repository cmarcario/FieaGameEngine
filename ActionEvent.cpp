#include "pch.h"
#include "ActionEvent.h"
#include "EventMessageAttributed.h"
#include "Event.h"
#include <memory>

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionEvent);

	ActionEvent::ActionEvent(EventQueue* eventQueue) : Action(TypeIdInstance()), m_EventQueue(eventQueue) {}

	const Vector<Signature> ActionEvent::Signatures()
	{
		return Vector<Signature>
			({
				Signature("m_Name", Datum::DatumTypes::STRING, 1, offsetof(ActionEvent, m_Name)),
				Signature("m_Subtype", Datum::DatumTypes::STRING, 1, offsetof(ActionEvent, m_Subtype)),
				Signature("m_Delay", Datum::DatumTypes::INTEGER, 1,  offsetof(ActionEvent, m_Delay)),
				Signature("m_EventQueue", Datum::DatumTypes::POINTER, 1,  offsetof(ActionEvent, m_EventQueue)),
			});
	}

	ActionEvent* ActionEvent::Clone()
	{
		return new ActionEvent(*this);
	}

	EventQueue* ActionEvent::GetEventQueue() const
	{
		return m_EventQueue;
	}

	void ActionEvent::SetEventQueue(EventQueue& eventQueue)
	{
		m_EventQueue = &eventQueue;
	}

	const std::string& ActionEvent::GetSubtype() const
	{
		return m_Subtype;
	}

	void ActionEvent::SetSubtype(const std::string& subtype)
	{
		m_Subtype = subtype;
	}

	const int ActionEvent::GetDelay() const
	{
		return m_Delay;
	}

	void ActionEvent::SetDelay(int delay)
	{
		m_Delay = delay;
	}

	void ActionEvent::Update(WorldState& worldState)
	{
		worldState.m_CurrentAction = this;
		if (m_EventQueue == nullptr)
		{
			throw std::runtime_error("event queue cannot be null");
		}

		EventMessageAttributed message;
		message.SetSubtype(m_Subtype);
		message.SetWorldState(worldState);

		for (auto& pair : AuxiliaryAttributes())
		{
			Datum& datum = message.AppendAuxiliaryAttribute(pair->first);
			datum = pair->second;
		}

		shared_ptr<Event<EventMessageAttributed>> event = make_shared<Event<EventMessageAttributed>>(message);

		m_EventQueue->Enqueue(event, std::chrono::milliseconds(m_Delay));
		worldState.m_CurrentAction = nullptr;

	}
}