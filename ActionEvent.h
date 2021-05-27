#pragma once
#include "Action.h"
#include "Factory.h"
#include "EventQueue.h"
#include "Signature.h"

namespace FieaGameEngine
{
	class ActionEvent : public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action);
	public:
		ActionEvent(EventQueue* eventQueue = nullptr);
		void Update(WorldState& worldState) override;

		ActionEvent* Clone() override;

		EventQueue* GetEventQueue() const;
		void SetEventQueue(EventQueue& eventQueue);

		const std::string& GetSubtype() const;
		void SetSubtype(const std::string& subtype);

		const int GetDelay() const;
		void SetDelay(int delay);

		static const Vector<Signature> Signatures();

	private:
		std::string m_Subtype;
		int m_Delay = 0;
		EventQueue* m_EventQueue;
	};

	ConcreteFactory(ActionEvent, Scope)
}

