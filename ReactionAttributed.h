#pragma once
#include "Reaction.h"
#include "Factory.h"

namespace FieaGameEngine
{
	/// <summary>
	/// ReactionAttributed class
	/// subscribes to Event<EventMessageAttribute>
	/// WILL FAIL if it is subscribed to another kind of event
	/// copies arguments into itself and then calls update upon notify
	/// </summary>
	class ReactionAttributed : public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed, Reaction);

	public:
		/// <summary>
		/// ReactionAttributed constructor
		/// subscribes to Event<EvetnMessageAttributed>
		/// </summary>
		ReactionAttributed();

		/// <summary>
		/// ReactionAttributed destructor
		/// unsubscribes from Event<EvetnMessageAttributed>
		/// </summary>
		~ReactionAttributed();

		/// <summary>
		/// default reaction attributed copy constructor
		/// </summary>
		ReactionAttributed(const ReactionAttributed&) = default;

		/// <summary>
		/// default reaction attributed move constructor
		/// </summary>
		ReactionAttributed(ReactionAttributed&&) = default;

		/// <summary>
		/// default reaction attributed copy assignemnt operator
		/// </summary>
		ReactionAttributed& operator=(const ReactionAttributed&) = default;

		/// <summary>
		/// default reaction attributed move assignemnt operator
		/// </summary>
		ReactionAttributed& operator=(ReactionAttributed&&) = default;

		/// <summary>
		/// checks the messages subtype against its own subtype(s)
		/// if theres a match, copy its auxiliary attributes into itself and calls action lists update
		/// </summary>
		/// <param name="eventPub">the event that notified us</param>
		void Notify(const EventPublisher& eventPub) override;

		/// <summary>
		/// returns a heap allocated copy of itself
		/// </summary>
		/// <returns>a heap allocated copy of itself</returns>
		ReactionAttributed* Clone() override;

		/// <summary>
		/// returns the subtype it processes
		/// </summary>
		/// <returns>the subtype it processes</returns>
		const std::string& GetSubtype() const;
		
		/// <summary>
		/// sets the subtype it processes to the passed in value
		/// </summary>
		/// <param name="subtype">the subtype to set</param>
		void SetSubtype(const std::string& subtype);

		/// <summary>
		/// returns a vecotor of its prescribed attribute signatures
		/// </summary>
		/// <returns>the vector of its signatures</returns>
		static const Vector<Signature> Signatures();

	protected:
		/// <summary>
		/// the subtype that it processes
		/// </summary>
		std::string m_Subtype;

		/// <summary>
		/// the key that is used for the subtype datum
		/// </summary>
		inline static const std::string m_SubtypeKey = "m_Subtype";
	};

	ConcreteFactory(ReactionAttributed, Scope);
}
