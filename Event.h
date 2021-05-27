#pragma once
#include "EventPublisher.h"
#include "EventSubscriber.h"
#include "Vector.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Event class
	/// Wraps a T and allows for usage of the eventQueue and its notify system
	/// </summary>
	template <typename T>
	class Event : public EventPublisher
	{
		RTTI_DECLARATIONS(Event, EventPublisher);

	public:
		/// <summary>
		/// event constructor
		/// takes in a T to copy and wrap as its message
		/// </summary>
		/// <param name="message">the T to copy and wrap as its message</param>
		Event(const T& message);

		/// <summary>
		/// event default copy constructor
		/// </summary>
		Event(const Event&) = default;

		/// <summary>
		/// event default move constructor
		/// </summary>
		Event(Event&&) = default;

		/// <summary>
		/// event default destructor
		/// </summary>
		~Event() = default;

		/// <summary>
		/// event default copy assignment operator
		/// </summary>
		Event& operator=(const Event&) = default;

		/// <summary>
		/// event default move assignment operator
		/// </summary>
		Event& operator=(Event&&) = default;

		/// <summary>
		/// returns the message wrapped by this event
		/// </summary>
		/// <returns>the message wrapped by this event</returns>
		const T& Message() const;

		/// <summary>
		/// adds a subscriber to the list of subscribers
		/// </summary>
		/// <param name="subscriber">the subscriber to add</param>
		static void Subscribe(EventSubscriber& subscriber);

		/// <summary>
		/// removes a subscriber from the list of subscribers
		/// </summary>
		/// <param name="subscriber">the subscriber to remove</param>
		static void Unsubscribe(EventSubscriber& subscriber);

		/// <summary>
		/// removes all the subscribers from the list and frees the memory
		/// </summary>
		static void UnsubscribeAll();

	private:
		/// <summary>
		/// the list of subscribers to this event
		/// </summary>
		static Vector<EventSubscriber*> m_Subscribers;

		/// <summary>
		/// the message wrapped by this event
		/// </summary>
		T m_Message;
	};
}

#include "Event.inl"
