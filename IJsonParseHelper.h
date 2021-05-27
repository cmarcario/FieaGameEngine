#pragma once
#include <string>
#include <json/json.h>
#include "JsonParseCoordinator.h"
#include "RTTI.h"

namespace FieaGameEngine
{
	/// <summary>
	/// IJsonParseHelper class
	/// abstract class
	/// takes in a json value and parses that data to the appropriate type, if it is compatible with the helper in question
	/// </summary>
	class IJsonParseHelper : public RTTI
	{
		RTTI_DECLARATIONS(IJsonParseHelper, RTTI);
	public:
		/// <summary>
		/// Initializes the helper
		/// </summary>
		virtual void Initialize();

		/// <summary>
		/// chekcs if certain helper can handle incoming data
		/// if so, parses the value and pushes it into the shared data
		/// to be implemented in a derived class
		/// </summary>
		/// <param name="data">the shared data to push into</param>
		/// <param name="key">they key that determines whether or not this handler can parse this thing</param>
		/// <param name="value">the value to be parsed</param>
		/// <param name="isArray">whether or not the value is an array</param>
		/// <returns>whether or not this helper handles this data type</returns>
		virtual bool StartHandler(JsonParseCoordinator::SharedData& data, const std::string& key, const Json::Value& value, bool isArray) = 0;

		/// <summary>
		/// finished any processes started by startHandler and returns whether or not it succeeded
		/// to be implemented in a derived class
		/// </summary>
		/// <param name="data">the shared data being used</param>
		/// <param name="key">the key that determines whether or not this helper can take this data</param>
		/// <returns>whenter or not the handler could end the process</returns>
		virtual bool EndHandler(JsonParseCoordinator::SharedData& data, const std::string& key) = 0;

		/// <summary>
		/// creates a new helper of its type
		/// to be implemented in a derived class
		/// </summary>
		/// <returns>the new helper</returns>
		virtual IJsonParseHelper* Create() const = 0;
	};
}