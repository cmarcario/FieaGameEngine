#pragma once
#include "IJsonParseHelper.h"
#include "Scope.h"
#include "JsonParseCoordinator.h"
#include "Stack.h"

namespace FieaGameEngine
{
	/// <summary>
	/// TableParseHelper class
	/// handles the parsing of data from a json file into a scope
	/// works with the following grammar:
	///		"AttributeName: {
	///			"type": "attributeType",
	///			"value": value of the attribute
	///		}
	/// the attribute type should correspond with a datum type, save for pointer.
	/// floats and ints can be the raw values, vectors and matrices must be represented as strings.
	/// tables should be sub-objects under value.
	/// </summary>
	class TableParseHelper : public IJsonParseHelper
	{
		RTTI_DECLARATIONS(TableParseHelper, IJsonParseHelper);

	public:
		/// <summary>
		/// SharedData class for TableParseHelper
		/// contains the scope being written to
		/// </summary>
		class SharedData final : public JsonParseCoordinator::SharedData
		{
			friend TableParseHelper;
			RTTI_DECLARATIONS(SharedData, JsonParseCoordinator::SharedData);

		public:
			explicit SharedData(Scope& root);
			SharedData() = default;

			/// <summary>
			/// initializes the shared data object
			/// clears out the root scope
			/// </summary>
			virtual void Initialize() override;

			/// <summary>
			/// creates a new empty shared data on the heap
			/// </summary>
			/// <returns>the new shared data</returns>
			virtual SharedData* Create() const override;

			/// <summary>
			/// the root scope being written to
			/// </summary>
			Scope* m_RootScope = nullptr;
		};

	private:
		/// <summary>
		/// StackFrame private struct
		/// is used by the start and end handlers
		/// stores a pointer to a scope, a pointer to a datum, and a reference to a key
		/// </summary>
		struct StackFrame
		{
			/// <summary>
			/// stackframe constructor
			/// takes in a scope reference, datum pointer, and string reference
			/// used to push a new stackframe onto the stack
			/// </summary>
			/// <param name="scope">the scope to be pushed</param>
			/// <param name="datum">the datum to be pushed</param>
			/// <param name="key">the key to be pushed</param>
			StackFrame(Scope& scope, Datum* datum, std::string attributeClass, const std::string& key);

			/// <summary>
			/// the scope to be appended to at any given time
			/// </summary>
			Scope* m_CurrentScope;

			/// <summary>
			/// the datum to be pushed to at any given time
			/// </summary>
			Datum* m_CurrentDatum;
			
			/// <summary>
			/// the current stored class to append
			/// </summary>
			std::string m_CurrentClass = "";

			/// <summary>
			/// the key of whatever is being parsed at the time
			/// </summary>
			const std::string& m_CurrentKey;
		};

	public:
		/// <summary>
		/// creates a new empty helper on the heap
		/// </summary>
		/// <returns>the new helper</returns>
		virtual IJsonParseHelper* Create() const override;

		/// <summary>
		/// initializes the helper
		/// </summary>
		virtual void Initialize() override;

		/// <summary>
		/// takes the data from the json file and parses it appropriately
		/// appends to the scope with the name of the attribute, sets its type to the type, and pushes back the value
		/// if the value is another scope, it creates a new scope and adopts it
		/// </summary>
		/// <param name="data">the shared data to append to</param>
		/// <param name="key">the key that determines which action to take</param>
		/// <param name="value">the value to be parsed</param>
		/// <param name="isArray">whether or not the data is an array, unreferenced</param>
		/// <returns>whether or not the handler was able to pushback the data</returns>
		/// <exception cref="std::runtime_error">throws an exception if the root scope is nullptr</exception>
		virtual bool StartHandler(JsonParseCoordinator::SharedData& data, const std::string& key, const Json::Value& value, bool isArray) override;

		/// <summary>
		/// pops whatever is on top of the stack off, if the keys are at the same address
		/// </summary>
		/// <param name="data">the data with the root scope, unreferenced</param>
		/// <param name="key">the key to be checked for the pop</param>
		/// <returns>whether or not the handler succeeded</returns>
		virtual bool EndHandler(JsonParseCoordinator::SharedData& data, const std::string& key) override;

	private:
		/// <summary>
		/// helper functions that converts a json value to its intended type and pushes it back
		/// </summary>
		/// <param name="toPush">the value to be pushed</param>
		void SetInt(const Json::Value& toPush);
		void SetFloat(const Json::Value& toPush);
		void SetString(const Json::Value& toPush);
		void SetVector(const Json::Value& toPush);
		void SetMatrix(const Json::Value& toPush);

		/// <summary>
		/// array of the pushback functions
		/// used by starthandler to push the values into the top datum via dynamic dispatch
		/// </summary>
		using SetFunctions = void(TableParseHelper::*)(const Json::Value& toPush);
		inline static const SetFunctions m_SetFunctions[static_cast<int>(Datum::DatumTypes::MATRIX) + 1] =
		{
			&TableParseHelper::SetInt, //int
			&TableParseHelper::SetFloat, //float
			&TableParseHelper::SetString, //string
			&TableParseHelper::SetVector, //vector
			&TableParseHelper::SetMatrix, //matrix
		};

		/// <summary>
		/// the stack of stackframes (scope, datum, key)
		/// whatever is on top is the scope/datum/key that are currently being appended to
		/// </summary>
		Stack<StackFrame> m_Stack;
	};
}