#pragma once
#include "EventPublisher.h"

namespace FieaGameEngine
{
	class EventSubscriber
	{
	public:
		/// <summary>
		/// virtual event subscriber destructor
		/// </summary>
		virtual ~EventSubscriber() {};

		/// <summary>
		/// the code to be run when the event is delivered and the subscriber is notified
		/// functionality is dependant upon the child implementation
		/// </summary>
		virtual void Notify(const EventPublisher&) = 0;
	};
}

