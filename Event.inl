#include "Event.h"

namespace FieaGameEngine
{
	template <typename T>
	Vector<EventSubscriber*> Event<T>::m_Subscribers;

	template <typename T>
	RTTI_DEFINITIONS(Event<T>);

	template<typename T>
	inline Event<T>::Event(const T& message) : EventPublisher(m_Subscribers), m_Message(message) {}

	template<typename T>
	inline const T& Event<T>::Message() const
	{
		return m_Message;
	}

	template<typename T>
	inline void Event<T>::Subscribe(EventSubscriber& subscriber)
	{
		m_Subscribers.PushBack(&subscriber);
	}

	template<typename T>
	inline void Event<T>::Unsubscribe(EventSubscriber& subscriber)
	{
		m_Subscribers.Remove(&subscriber);
	}

	template<typename T>
	inline void Event<T>::UnsubscribeAll()
	{
		m_Subscribers.Clear();
		m_Subscribers.ShrinkToFit();
	}
}
