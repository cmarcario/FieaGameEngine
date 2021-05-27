#pragma once
#include "RTTI.h"
#include "Vector.h"

namespace FieaGameEngine
{
	class IJsonParseHelper;

	/// <summary>
	/// JsonParseCoordinator class
	/// keeps track of the helpers and passes in json values for them to handle
	/// </summary>
	class JsonParseCoordinator : public RTTI
	{
		RTTI_DECLARATIONS(JsonParseCoordinator, RTTI);
	public:
		/// <summary>
		/// SharedData abstract class
		/// stores the data that is being parsed
		/// is inherited by the helpers
		/// </summary>
		class SharedData : public RTTI
		{
			RTTI_DECLARATIONS(SharedData, RTTI);
			friend JsonParseCoordinator;
		public:

			/// <summary>
			/// shared data default constructor
			/// </summary>
			SharedData() = default;

			/// <summary>
			/// shared data default copy constructor
			/// </summary>
			SharedData(const SharedData&) = default;

			/// <summary>
			/// shared data default move constructor
			/// </summary>
			SharedData(SharedData&&) = default;

			/// <summary>
			/// shared data pure virtual destructor
			/// </summary>
			~SharedData() = 0 {};

			/// <summary>
			/// shared data default copy assignemnt operator
			/// </summary>
			SharedData& operator=(const SharedData&) = default;

			/// <summary>
			/// shared data default move assignment operator
			/// </summary>
			SharedData& operator=(SharedData&&) = default;

			/// <summary>
			/// initializes the shared data
			/// </summary>
			virtual void Initialize();

			/// <summary>
			/// creates a new shared data of the type
			/// pure virtual
			/// </summary>
			/// <returns>pointer the new shared data</returns>
			virtual SharedData* Create() const = 0;

			/// <summary>
			/// gets the JsonParseCoordinator associated with the shared data
			/// </summary>
			/// <returns>the JsonParseCoordinator associated with the shared data</returns>
			JsonParseCoordinator* GetJsonParseCoordinator();

			/// <summary>
			/// const version of GetJsonParseCoordinator
			/// gets the JsonParseCoordinator associated with the shared data
			/// </summary>
			/// <returns>the JsonParseCoordinator associated with the shared data</returns>
			const JsonParseCoordinator* GetJsonParseCoordinator() const;

			/// <summary>
			/// increases the current depth
			/// </summary>
			void IncrementDepth();

			/// <summary>
			/// decreases the current depth
			/// </summary>
			void DecrementDepth();

			/// <summary>
			/// returns the current depth
			/// </summary>
			/// <returns></returns>
			size_t Depth();

		private:
			/// <summary>
			/// sets the jsonParseCoordinator associated with this shared data
			/// </summary>
			/// <param name="toSet">the coordinator to set to</param>
			void SetJsonParseCoordinator(JsonParseCoordinator* toSet);

			/// <summary>
			/// the parse coordinator associated with this shared data
			/// </summary>
			JsonParseCoordinator* m_ParseCoordinator = nullptr;

			/// <summary>
			/// the current depth
			/// </summary>
			size_t m_NestingDepth = 0;
		};

	public:
		/// <summary>
		/// constructor for JsonParseCoordinator
		/// takes in a sharedData and sets its own shared data pointer to point to it
		/// also sets the sharedData's coordinator pointer to itself
		/// </summary>
		/// <param name="data">the shared data to set</param>
		explicit JsonParseCoordinator(SharedData& data);

		/// <summary>
		/// default constructor for shared data
		/// </summary>
		JsonParseCoordinator() = default;

		/// <summary>
		/// deleted copy constructor
		/// </summary>
		JsonParseCoordinator(const JsonParseCoordinator&) = delete;

		/// <summary>
		/// deleted copy assignment constructor
		/// </summary>
		JsonParseCoordinator& operator=(const JsonParseCoordinator&) = delete;

		/// <summary>
		/// move constructor for JsonParseCoordinator
		/// </summary>
		/// <param name="toMove">the coordinator to be moved</param>
		/// <returns>the moved coordinator</returns>
		JsonParseCoordinator(JsonParseCoordinator&& toMove) noexcept;

		/// <summary>
		/// move assignment operator for JsonParseCoordinator
		/// </summary>
		/// <param name="toMove">the coordinator to be moved</param>
		/// <returns>the moved coordinator</returns>
		JsonParseCoordinator& operator=(JsonParseCoordinator&& toMove) noexcept;

		/// <summary>
		/// destructor for JsonParseCoordinator
		/// </summary>
		~JsonParseCoordinator();

		/// <summary>
		/// makes a blank copy of the current coordinator
		/// has the same helpers and shared data, but they are empty and not actively doing anything
		/// </summary>
		/// <returns>the new coordinator</returns>
		JsonParseCoordinator* Clone() const;

		/// <summary>
		/// returns the current list of helpers
		/// </summary>
		/// <returns>the current list of helpers</returns>
		const Vector<IJsonParseHelper*>& Helpers() const;

		/// <summary>
		/// gets the current shared data associated with this coordinator 
		/// </summary>
		/// <returns>the current shared data associated with this coordinator </returns>
		SharedData& GetSharedData();

		/// <summary>
		/// const version of GetSharedData
		/// gets the current shared data associated with this coordinator 
		/// </summary>
		/// <returns>the current shared data associated with this coordinator </returns>
		const SharedData& GetSharedData() const;

		/// <summary>
		/// sets the shared data associated with this corrdinator
		/// also sets that datas coordinaor to this
		/// </summary>
		/// <param name="toSet">the shared data to be set</param>
		void SetSharedData(SharedData& toSet);

		/// <summary>
		/// adds a helper to the list of helpers
		/// </summary>
		/// <param name="helper">the helper to add</param>
		void AddHelper(IJsonParseHelper& helper);

		/// <summary>
		/// removes a helper from the list of helpers
		/// </summary>
		/// <param name="helper">the helper to remove</param>
		void RemoveHelper(IJsonParseHelper& helper);

		/// <summary>
		/// returns whether or not the coordinator is a clone
		/// </summary>
		/// <returns>whether or not the coordinator is a clone</returns>
		bool IsClone() const;

		/// <summary>
		/// parses values from a string of json data
		/// </summary>
		/// <param name="toParse">the string to parse</param>
		void Parse(const std::string& toParse);

		/// <summary>
		/// parses values from an istream of json data
		/// </summary>
		/// <param name="stream">the string to parse</param>
		void Parse(std::istream& stream);

		/// <summary>
		/// parses data from a json file
		/// </summary>
		/// <param name="fileName">the name of the file to be parsed</param>
		void ParseFromFile(const std::string& fileName);

	private:
		/// <summary>
		/// deletes heap allocated helpers
		/// </summary>
		void DeleteHelpers();

		/// <summary>
		/// goes through the members of a json value and parses them
		/// </summary>
		/// <param name="root">the root value to parse</param>
		void ParseMembers(const Json::Value& root);

		/// <summary>
		/// takes in a key and a value, goes through the helpers to see if any of them can handle the passed in data 
		/// if so, it calls the start and end handlers on the helper
		/// </summary>
		/// <param name="key">the key to see if the helpers can take the data</param>
		/// <param name="value">the value to be parsed</param>
		void Parse(const std::string& key, const Json::Value& value);

		/// <summary>
		/// the list of helpers in this coordinator
		/// </summary>
		Vector<IJsonParseHelper*> m_Helpers;

		/// <summary>
		/// pointer to this coordinators shared data
		/// </summary>
		SharedData* m_SharedData = nullptr;

		/// <summary>
		/// whether or not this cooridnator is a clone;
		/// </summary>
		bool m_IsClone = false;
	};
}

