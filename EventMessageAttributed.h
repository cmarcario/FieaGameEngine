#pragma once
#include "Attributed.h"
#include "WorldState.h"
#include <string>
#include "Signature.h"

namespace FieaGameEngine
{
	/// <summary>
	/// EventMessageAttributed class
	/// inherits from attributed
	/// used in events for ReactionAttributed
	/// </summary>
	class EventMessageAttributed : public Attributed
	{
		RTTI_DECLARATIONS(EventMessageAttributed, Attributed);

	public:
		/// <summary>
		/// EventMessageAttributed constructor
		/// passes its rtti id to the attributed constructor
		/// </summary>
		EventMessageAttributed();

		/// <summary>
		/// default event message attributed copy constructor
		/// </summary>
		EventMessageAttributed(const EventMessageAttributed&) = default;

		//// <summary>
		/// default event message attributed move constructor
		/// </summary>
		EventMessageAttributed(EventMessageAttributed&&) = default;

		/// <summary>
		/// default eventMessageAttributed destructor
		/// </summary>
		~EventMessageAttributed() = default;

		/// <summary>
		/// default event message attributed copy assignment operator
		/// </summary>
		EventMessageAttributed& operator=(const EventMessageAttributed&) = default;

		/// <summary>
		/// default event message attributed move assignment operator
		/// </summary>
		EventMessageAttributed& operator=(EventMessageAttributed&&) = default;
		
		/// <summary>
		/// returns a heap allocated copy of itself
		/// </summary>
		/// <returns>a heap allocated copy of itself</returns>
		EventMessageAttributed* Clone() override;

		/// <summary>
		/// returns the subtype the message is
		/// </summary>
		/// <returns>the subtype the message is</returns>
		const std::string& GetSubtype() const;

		/// <summary>
		/// sets the subtype to the given value
		/// </summary>
		/// <param name="subtype">the subtype to set</param>
		void SetSubtype(const std::string& subtype);

		/// <summary>
		/// gets the worldstate associated with this message
		/// </summary>
		/// <returns>the worldstate associated with this message</returns>
		WorldState* GetWorldState() const;

		/// <summary>
		/// sets the worldstate to the passed in value
		/// </summary>
		/// <param name="worldState">the worldstate to set</param>
		void SetWorldState(WorldState& worldState);

		/// <summary>
		/// vector of eventmessageattributeds prescribed attribute signatures
		/// </summary>
		/// <returns>the vector of the signatures</returns>
		static const Vector<Signature> Signatures();

	protected:
		/// <summary>
		/// the subtype of this message
		/// </summary>
		std::string m_Subtype;

		/// <summary>
		/// the worldstate associated with this message
		/// </summary>
		WorldState* m_WorldState;
	};
}

