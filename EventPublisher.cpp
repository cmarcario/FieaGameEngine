#include "pch.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(EventPublisher);

	EventPublisher::EventPublisher(const Vector<EventSubscriber*>& subscribers) : 
		m_Subscribers(&subscribers) {};

	void EventPublisher::Deliver() const
	{
		for (EventSubscriber* subscriber : *m_Subscribers)
		{
			assert(subscriber != nullptr);
			subscriber->Notify(*this);
		}
	}
}