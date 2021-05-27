#pragma once
#include "HashMap.h"
#include "Datum.h"
#include "RTTI.h"
#include "Factory.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Scope class
	/// stores a map of strings to datums, and also records the order of which they were inserted
	/// also is aware of who it's parent scope is, if any
	/// </summary>
	class Scope : public FieaGameEngine::RTTI
	{
		RTTI_DECLARATIONS(Scope, RTTI);

	public:
		using KeyType = const std::string;
		using MapType = HashMap<KeyType, Datum>;

	protected:
		using MapPairType = MapType::PairType;
		using MapIterator = MapType::Iterator; 
		using MapConstIterator = MapType::ConstIterator; 


	public:
		/// <summary>
		/// constructor for scope
		/// sets both the map and the vector to a passed in size, or uses the default map size for both
		/// </summary>
		/// <param name="size">the size to make the map and vector</param>
		explicit Scope(size_t size = 11);

		/// <summary>
		/// copy constructor for scope
		/// takes in a reference to another scope and copies its members
		/// note: it does NOT parent the scope to the passed in scope's parent
		/// </summary>
		/// <param name="toCopy">the scope to be copied</param>
		Scope(const Scope& toCopy);

		/// <summary>
		/// move constructor for scope
		/// moves the memory from one scope to another
		/// reparents this scope, and updates all its childrens parent pointers
		/// </summary>
		/// <param name="toMove">the scope to be moved</param>
		/// <returns>the moved scope</returns>
		Scope(Scope&& toMove) noexcept;

		/// <summary>
		/// destructor for scope
		/// calls clear
		/// </summary>
		virtual ~Scope();

		/// <summary>
		/// copy assignment operator for scope
		/// operates the same way as the copy constructor, but with an already existent scope
		/// calls clear before copying
		/// </summary>
		/// <param name="toCopy">the scope to be copied</param>
		/// <returns>the newly copied scope</returns>
		Scope& operator=(const Scope& toCopy);

		/// <summary>
		/// move operator for scope
		/// moves the memory from one scope to another
		/// reparents this scope, and updates all its childrens parent pointers
		/// </summary>
		/// <param name="toMove">the scope to be moved</param>
		/// <returns>the moved scope</returns>
		Scope& operator=(Scope&& toMove) noexcept;

		/// <summary>
		/// operator [] that takes in a const std::string key
		/// returns the datum at that key, or creates one if none is found
		/// </summary>
		/// <param name="key">the key to return the datum at</param>
		/// <returns>the datum at that key, or the new datum if the key was not present</returns>
		Datum& operator[](KeyType key);

		/// <summary>
		/// operator [] that takes in a size_t index
		/// returns the datum at the passed in index
		/// </summary>
		/// <param name="index">the index to return the datum at</param>
		/// <returns>the datum at that index</returns>
		Datum& operator[](size_t index);

		/// <summary>
		/// == operator for scope
		/// returns whether or not two scopes are equal
		/// </summary>
		/// <param name="toCompare">the scope to be compared</param>
		/// <returns>whether or not the two scopes are the same</returns>
		bool operator==(const Scope& toCompare);

		/// <summary>
		/// != operator for scope
		/// returns whether or not two scopes are not equal
		/// </summary>
		/// <param name="toCompare">the scope to be compared</param>
		/// <returns>whether or not the two scopes are not the same</returns>
		bool operator!=(const Scope& toCompare);

		/// <summary>
		/// the override for the RTTI Equals() function
		/// </summary>
		/// <param name="rhs">the pointer that should contain the scope to be compared</param>
		/// <returns>whether or not the two scopes are equal</returns>
		/// <exception cref="runtime_error"> throws an exception if the pointer passed in is not that of a scope</exception>
		bool Equals(const RTTI* rhs) const override;

		/// <summary>
		/// overridable constructor of a sort
		/// returns a copy of itself
		/// </summary>
		/// <returns>a copy of whatever scope it was called on</returns>
		virtual Scope* Clone();

		/// <summary>
		/// adds a new datum to the scope based off the passed in key
		/// if the key already exists, return the datum already present
		/// </summary>
		/// <param name="key">the key to be appended</param>
		/// <returns>the datum associated the key, whether or not it was just created</returns>
		/// <exception cref="runtime_error">throws an exception if the passed in string is empty</exception>
		Datum& Append(KeyType& key);

		/// <summary>
		/// adds a new table datum based on the passed in key
		/// heap allocates a new scope and pushes it back on the key 
		/// sets the new scopes owner to this
		/// </summary>
		/// <param name="key">the key to be appended</param>
		/// <returns>the newly allocated scope</returns>
		/// <exception cref="runtime_error">throws an exception if the string is empty</exception>
		Scope& AppendScope(KeyType& key);

		/// <summary>
		/// takes in a scope and reparents it to this at a specific key
		/// if it already has an owner, it calls orphan
		/// </summary>
		/// <param name="toAdopt">the scope to be adopted</param>
		/// <param name="key">the key to put the scope at</param>
		/// <exception cref="rutime_error">throws an exception if the datum at the passed in key is not a table</exception>
		void Adopt(Scope& toAdopt, KeyType& key);

		/// <summary>
		/// removes the scope from its parent
		/// </summary>
		void Orphan();

		/// <summary>
		/// returns the size of the scope
		/// </summary>
		/// <returns>the number of pairs within the scope</returns>
		size_t Size() const;

		/// <summary>
		/// finds a certain datum based off the key
		/// </summary>
		/// <param name="key">the key to find the datum at</param>
		/// <returns>the key at the datum</returns>
		const Datum* Find(KeyType& key) const;

		/// <summary>
		/// non-const version of find
		/// finds a certain datum based off the key
		/// </summary>
		/// <param name="key">the key to find the datum at</param>
		/// <returns>the key at the datum</returns>
		Datum* Find(KeyType& key);

		/// <summary>
		/// finds a scope within itself or its children
		/// does not search the parent(s)
		/// returns nullptr and 0 if it is not found
		/// </summary>
		/// <param name="toFind">the scope to be found</param>
		/// <returns>the datum the scope is in and the index its at within said datum</returns>
		std::pair<Datum*, size_t> FindContainedScope(Scope& toFind);

		/// <summary>
		/// searches up the hierarchy for a key
		/// returns two nullptrs if not found
		/// </summary>
		/// <param name="key">the key to be found</param>
		/// <returns></returns>
		std::pair<Datum*, Scope*> Search(KeyType& key);

		/// <summary>
		/// returns the scopes parent scope, if any
		/// </summary>
		/// <returns>the scopes parent scope</returns>
		Scope* GetParent();

		/// <summary>
		/// clears out the scope
		/// deletes any children scope, and empties the map and the vector
		/// </summary>
		void Clear();

	protected:
		/// <summary>
		/// checks to see if this is a descendant of the passed in scope
		/// </summary>
		/// <param name="toCheck">the scope to be checked</param>
		/// <returns>whether or not we are descended from that </returns>
		bool IsDescendantOf(Scope& toCheck);

		/// <summary>
		/// helper functions that throws if a string is empty
		/// </summary>
		/// <param name="key">the string to be checked</param>
		/// <exception cref="runtime_error">throws an exception if the string is empty</exception>
		void EmptyStringCheck(KeyType& key);

		/// <summary>
		/// the scope's parent
		/// </summary>
		Scope* m_Parent = nullptr;

		/// <summary>
		/// the order that string datum pairs were inserted into the scope
		/// </summary>
		Vector<MapPairType*> m_Order;

		/// <summary>
		/// the map of the string datum pairs
		/// </summary>
		MapType m_Map;
	};

	ConcreteFactory(Scope, Scope);
}

