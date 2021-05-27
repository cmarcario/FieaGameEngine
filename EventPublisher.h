#pragma once
#include "RTTI.h"
#include "Vector.h"

namespace FieaGameEngine
{
	class EventSubscriber;

	/// <summary>
	/// EventPublisher class
	/// to be inherited by Event
	/// allows iteration through subscribers to call their notify methods
	/// </summary>
	class EventPublisher : public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI);

	public:
		/// <summary>
		/// event publisher default copy constructor
		/// </summary>
		EventPublisher(const EventPublisher&) = default;

		/// <summary>
		/// event publisher default move constructor
		/// </summary>
		EventPublisher(EventPublisher&&) = default;

		/// <summary>
		/// event publisher default destructor
		/// </summary>
		~EventPublisher() = default;

		/// <summary>
		/// event publisher default copy assignmetn operator
		/// </summary>
		EventPublisher& operator=(const EventPublisher&) = default;

		/// <summary>
		/// event publisher default move assintment operator
		/// </summary>
		EventPublisher& operator=(EventPublisher&&) = default;

		/// <summary>
		/// iterates through the list of subscribers and calls their notify methods
		/// </summary>
		void Deliver() const;

	protected:
		/// <summary>
		/// event publisher constructor
		/// takes in a list of subscribers and saves the pointer to it
		/// </summary>
		/// <param name="subscribers">the subscribers to save</param>
		EventPublisher(const Vector<EventSubscriber*>& subscribers);

		/// <summary>
		/// a pointer to the list of subscribers to iterate through
		/// </summary>
		const Vector<EventSubscriber*>* m_Subscribers;
	};
}

