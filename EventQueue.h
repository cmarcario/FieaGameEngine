#pragma once
#include <chrono>
#include <memory>
#include "RTTI.h"
#include "GameTime.h"
#include "Vector.h"
#include "EventPublisher.h"

namespace FieaGameEngine
{
	/// <summary>
	/// EventQueue class
	/// Stores pointers to events and time information into a queue, and iterates through and checks whether or not said event needs to be delivered based on the gametime
	/// Deliveres any events that need delivering
	/// </summary>
	class EventQueue final : public RTTI
	{
		RTTI_DECLARATIONS(EventQueue, RTTI);
	public:
		/// <summary>
		/// EventQueue constructor
		/// takes in a reference to a gametime to use for its time based functions
		/// </summary>
		/// <param name="gameTime">the game time to use</param>
		EventQueue(GameTime& gameTime);

		/// <summary>
		/// event queue default copy constructor
		/// </summary>
		EventQueue(const EventQueue&) = default;

		/// <summary>
		/// event queue default move constructor
		/// </summary>
		EventQueue(EventQueue&&) = default;

		/// <summary>
		/// event queue default destructor
		/// </summary>
		~EventQueue() = default;

		/// <summary>
		/// event queue default copy assignment operator
		/// </summary>
		EventQueue& operator=(const EventQueue&) = default;

		/// <summary>
		/// event queue default move assignment operator
		/// </summary>
		EventQueue& operator=(EventQueue&&) = default;

		/// <summary>
		/// adds a new event to the queue, with its delay and the current time
		/// </summary>
		/// <param name="publisher">the event to be queued</param>
		/// <param name="delay">the delay that that event should have before delivering</param>
		void Enqueue(const std::shared_ptr<EventPublisher>& publisher, std::chrono::milliseconds delay = std::chrono::milliseconds(0));

		/// <summary>
		/// partitions the event queue based upon whether or not they are expired
		/// calls deliver on the expired events, then removes them from the queue
		/// </summary>
		void Update();

		/// <summary>
		/// returns the number of elements in the queue
		/// </summary>
		/// <returns>the number of elements in the queue</returns>
		size_t Size();

		/// <summary>
		/// empties the queue
		/// </summary>
		void Clear();

		/// <summary>
		/// returns whether or not the array is empty
		/// </summary>
		/// <returns>whether or not the array is empty</returns>
		bool IsEmpty();

	private:
		/// <summary>
		/// stores the information needed for each entry in the queue
		/// </summary>
		struct QueueEntry
		{
			/// <summary>
			/// pointer to the event that is in the queue
			/// </summary>
			std::shared_ptr<EventPublisher> m_Event;

			/// <summary>
			/// the time that the event was enqueued 
			/// </summary>
			std::chrono::high_resolution_clock::time_point m_TimeEnqueued;

			/// <summary>
			/// how long the event should be delayed
			/// </summary>
			std::chrono::milliseconds m_Delay;

			/// <summary>
			/// compares the delay and the time enqueued to the current time and returns whether or not the former is greater than the latter (i.e. the event is expired)
			/// </summary>
			/// <param name="currentTime">the current time to be checked</param>
			/// <returns>whether or not the event has expired</returns>
			bool IsExpired(std::chrono::high_resolution_clock::time_point currentTime) const;
		};
		/// <summary>
		/// the game time to be used for updating
		/// </summary>
		GameTime& m_GameTime;

		/// <summary>
		/// the queue of events to be delivered
		/// </summary>
		Vector<QueueEntry> m_EventQueue;
	};
}

