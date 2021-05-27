#pragma once
#include "HashMap.h"
#include "RTTI.h"
#include "Signature.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Type Manager class
	/// singelton class that manages the signatures for any added types
	/// </summary>
	class TypeManager final
	{
	public:
		using SignatureList = Vector<Signature>;

		/// <summary>
		/// deleted constructor for TypeManager since the class is static
		/// </summary>
		TypeManager() = delete;

		/// <summary>
		/// deleted copy constructor
		/// </summary>
		TypeManager(const TypeManager&) = delete;

		/// <summary>
		/// deleted move constructor
		/// </summary>
		TypeManager(TypeManager&&) = delete;

		/// <summary>
		/// defaulted destructor
		/// </summary>
		~TypeManager() = default;

		/// <summary>
		/// deleted copy assignment operator
		/// </summary>
		TypeManager& operator=(const TypeManager&) = delete;

		/// <summary>
		/// deleted move assignment operator
		/// </summary>
		TypeManager& operator=(TypeManager&&) = delete;

		/// <summary>
		/// adds a list of signatures based upon the rtti type id passed in
		/// </summary>
		/// <param name="id">the id of the type being added</param>
		/// <param name="signatures">the signatures of the type being added</param>
		static void AddType(RTTI::IdType id, SignatureList signatures);

		/// <summary>
		/// removes a list of signatures
		/// </summary>
		/// <param name="id">the type id of the signatures to be removed</param>
		static void RemoveType(RTTI::IdType id);

		/// <summary>
		/// returns the signatures of a given id type
		/// </summary>
		/// <param name="id">the type's id to get the signatures of</param>
		/// <returns>the signatures of that type</returns>
		static SignatureList GetSignatures(RTTI::IdType id);

		/// <summary>
		/// returns whether or not an id is in the map
		/// </summary>
		/// <param name="id">the id to check</param>
		/// <returns>whether or not they key is in the map</returns>
		static bool ContainsKey(RTTI::IdType id);
		
		/// <summary>
		/// returns the number of types in the map
		/// </summary>
		/// <returns>the number of types in the map</returns>
		static size_t Size();

		/// <summary>
		/// clears out the map
		/// </summary>
		static void Clear();

	private:
		using PairType = std::pair<const RTTI::IdType, SignatureList>;

		/// <summary>
		/// the hashmap that stores the id types and their signatures
		/// </summary>
		static HashMap<const RTTI::IdType, SignatureList> s_SignatureMap;
	};
}

