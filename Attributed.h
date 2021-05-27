#pragma once
#include "Scope.h"
#include "Vector.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Attributed class
	/// based on the signature of a child class, populates a scope with mirroring elements
	/// cannot be directly implemented, must be inherited from
	/// </summary>
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope);

	public:
		/// <summary>
		/// copy constructor for Attributed
		/// calls the copy constructor for scope and then updates the pointers
		/// </summary>
		/// <param name="toCopy">the attributed to be copied</param>
		Attributed(const Attributed& toCopy);

		/// <summary>
		/// move constructor for Attributed
		/// calls the move constructor for scope and then updates the pointers
		/// </summary>
		/// <param name="toMove">the Attributed to be moved</param>
		/// <returns>the new attributed</returns>
		Attributed(Attributed&& toMove) noexcept;

		/// <summary>
		/// destructor for attributed
		/// marked pure virtual
		/// </summary>
		virtual ~Attributed() = 0 {};

		/// <summary>
		/// copy assignment operator for Attributed
		/// calls the copy assignment operator for scope and then updates the pointers
		/// </summary>
		/// <param name="toCopy">the attributed to be copied</param>
		/// <returns>the copied attributed</returns>
		Attributed& operator=(const Attributed& toCopy);

		/// <summary>
		/// move assignment operator for Attributed
		/// calls the move assignment operator for scope and then updates the pointers</summary>
		/// <param name="toMove">the attributed to be moved</param>
		/// <returns>the moved attributed</returns>
		Attributed& operator=(Attributed&& toMove) noexcept;

		/// <summary>
		/// returns whether or not a key is an attribute
		/// </summary>
		/// <param name="key">the key to be checked</param>
		/// <returns>whether or not a key is an attribute</returns>
		bool IsAttribute(KeyType& key);

		/// <summary>
		/// returns whether or not a key is a prescribed attribute
		/// </summary>
		/// <param name="key">the key to be checked</param>
		/// <returns>whether or not a key is a prescribed attribute</returns>
		bool IsPrescribedAttribute(KeyType& key);

		/// <summary>
		/// returns whether or not a key is an auxiliary attribute
		/// </summary>
		/// <param name="key">the key to be checked</param>
		/// <returns>whether or not a key is an auxiliary attribute</returns>
		bool IsAuxiliaryAttribute(KeyType& key);

		/// <summary>
		/// appends an auxiliary attribute
		/// checkes if a key is a prescribed attribute, appends it if it is not
		/// </summary>
		/// <param name="key">the key to be checked and appended</param>
		/// <returns>a reference to the datum that was just appended</returns>
		Datum& AppendAuxiliaryAttribute(KeyType& key);

		/// <summary>
		/// returns all attributes in the attributed, regardless of if theyre prescribed or auxiliary attribute
		/// </summary>
		/// <returns>a vector of the attributes </returns>
		const Vector<MapPairType*>& Attributes();

		/// <summary>
		/// returns all prescribed attributes 
		/// </summary>
		/// <returns>a vector of the prescribed attributes</returns>
		const Vector<MapPairType*> PrescribedAttributes();

		/// <summary>
		/// returns all auxiliary attributes 
		/// </summary>
		/// <returns>a vector of the auxiliary attributes</returns>
		const Vector<MapPairType*> AuxiliaryAttributes() const;

	protected:
		/// <summary>
		/// constructor for attributed 
		/// set to protected as to not be called directly
		/// </summary>
		/// <param name="id">the type id of the class being instantiated</param>
		explicit Attributed(RTTI::IdType id);

	private:
		/// <summary>
		/// populates the scope based upon the child class's signatures
		/// </summary>
		/// <param name="id">the id of the class's signatures to get</param>
		void Populate(RTTI::IdType id);

		/// <summary>
		/// helper function for copy and move semantics
		/// updates the external pointers for the prescribed datums, as well as the this attribute
		/// </summary>
		/// <param name="other">the attributed to get the signatures of to update with</param>
		void UpdatePointers(const Attributed& other);
	};
}