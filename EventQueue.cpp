#include "pch.h"
#include "EventQueue.h"
#include <algorithm>

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(EventQueue);

	EventQueue::EventQueue(GameTime& gameTime) : m_GameTime(gameTime) {}

	void EventQueue::Enqueue(const std::shared_ptr<EventPublisher>& publisher, std::chrono::milliseconds delay)
	{
		QueueEntry entry
		{
			publisher,
			m_GameTime.CurrentTime(),
			delay
		};

		m_EventQueue.PushBack(entry);
	}

	void EventQueue::Update()
	{
		auto expiredStart = std::partition(m_EventQueue.begin(), m_EventQueue.end(),
			[this](QueueEntry queueEvent)
			{
				return !(queueEvent.IsExpired(m_GameTime.CurrentTime()));
			});

		for (auto it = expiredStart; it != m_EventQueue.end(); ++it)
		{
			(*it).m_Event->Deliver();
		}

		m_EventQueue.Remove(expiredStart, m_EventQueue.end());
	}

	size_t EventQueue::Size()
	{
		return m_EventQueue.Size();
	}

	void EventQueue::Clear()
	{
		m_EventQueue.Clear();
	}

	bool EventQueue::IsEmpty()
	{
		return m_EventQueue.IsEmpty();
	}

	bool EventQueue::QueueEntry::IsExpired(std::chrono::high_resolution_clock::time_point currentTime) const
	{
		return ((m_TimeEnqueued + m_Delay) <= currentTime);
	}

}