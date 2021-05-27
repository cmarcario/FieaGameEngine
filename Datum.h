#pragma once
#include <glm/glm.hpp>
#include <string>
#include <functional>
#include <map>
#include "RTTI.h"
#include "DefaultIncrement.h"

namespace FieaGameEngine
{
	class Scope;
	class Attributed;
	/// <summary>
	/// Datum class
	/// stores an array of values whos types can be determined at runtime
	/// </summary>
	class Datum final
	{
		friend Scope;
		friend Attributed;

	public:
		/// <summary>
		/// class of enums that determine the data types available to datum
		/// </summary>
		enum class DatumTypes
		{
			INTEGER = 0,
			FLOAT = 1,
			STRING = 2,
			VECTOR = 3,
			MATRIX = 4,
			TABLE = 5,
			POINTER = 6,
			UNKNOWN = 7,

			END = UNKNOWN
		};

		/// <summary>
		/// constructor for datum 
		/// takes in a type to set the datum to and sets said type, if any
		/// </summary>
		/// <param name="type">the type the datum is to be</param>
		explicit Datum(DatumTypes type = DatumTypes::UNKNOWN);

		/// <summary>
		/// copy constructor for datum
		/// copies over another datum's values into itself
		/// </summary>
		/// <param name="ToCopy">the datum to be copied</param>
		Datum(const Datum& ToCopy);

		/// <summary>
		/// move constructor for datum
		/// takes another datum's values for itself and resets the other datum to default
		/// </summary>
		/// <param name="ToMove">the datum to be moved</param>
		/// <returns>the new datum</returns>
		Datum(Datum&& ToMove) noexcept;

		/// <summary>
		/// destructor for datum
		/// destroys the values and frees the memory
		/// </summary>
		~Datum();

		/// <summary>
		/// copy assignment operator for datum 
		/// copies over another datum's values into itself
		/// </summary>
		/// <param name="ToCopy">the datum to be copied</param>
		/// <returns>the freshly copied datum</returns>
		Datum& operator=(const Datum& ToCopy);

		/// <summary>
		/// move assignment operator for datum
		/// takes another datum's values for itself and resets the other datum to default
		/// </summary>
		/// <param name="ToMove">the datum to be moved</param>
		/// <returns>the freshly moved datum</returns>
		Datum& operator=(Datum&& ToMove) noexcept;

		/// <summary>
		/// assigns the datum to the given value as though it were one instance
		/// one overload for each datum type
		/// </summary>
		/// <param name="value">the value to be set</param>
		/// <returns>the datum with the new value</returns>
		Datum& operator=(int value);
		Datum& operator=(float value);
		Datum& operator=(const std::string& value);
		Datum& operator=(const glm::vec4& value);
		Datum& operator=(const glm::mat4& value);
		Datum& operator=(Scope& value);
		Datum& operator=(RTTI* value);

		/// <summary>
		/// == operator
		/// returns whether or not the datum and the passed in datum are equal
		/// </summary>
		/// <param name="toCompare">the datum to be compared</param>
		/// <returns>whether or not the two datums are equal</returns>
		bool operator==(const Datum& toCompare) const;

		/// <summary>
		/// != operator
		/// returns whether or not the datum and the passed in datum are not equal
		/// </summary>
		/// <param name="toCompare">the datum to be compared</param>
		/// <returns>whether or not the two datums are not equal</returns>
		bool operator!=(const Datum& toCompare) const;

		/// <summary>
		/// sets the type of the datum
		/// </summary>
		/// <param name="type">the type to set the datum to</param>
		/// <exception cref="runtime_error">throws an exception if the type has already been set and the passed in type does not match</exception>
		void SetType(DatumTypes type);

		/// <summary>
		/// reserves the given amount of space
		/// </summary>
		/// <param name="capacity">the amount to be reserved</param>
		void Reserve(size_t capacity);

		/// <summary>
		/// resizes the datum to the given size\
		/// if it is larger, it expands the array and initializes default values in the extra space
		/// if it is smaller, it destructs the extra elements 
		/// </summary>
		/// <param name="size">the size to change to</param>
		void Resize(size_t size);

		/// <summary>
		/// returns the number of elements in the datum
		/// </summary>
		/// <returns>the number of elements in the datum</returns>
		size_t Size() const;

		/// <summary>
		/// returns the number of elements the datum can hold
		/// </summary>
		/// <returns>the number of elements the datum can hold</returns>
		size_t Capacity() const;

		/// <summary>
		/// returns the data type the datum stores
		/// </summary>
		/// <returns>the data type the datum stores</returns>
		DatumTypes Type() const;

		/// <summary>
		/// removes the elements from the datum
		/// </summary>
		void Clear();

		/// <summary>
		/// adds an int to the end of the array
		/// </summary>
		template <typename IncrementFunctor = DefaultIncrement>
		void PushBack(int value);
		
		/// <summary>
		/// adds a float to the end of the array
		/// </summary>
		template <typename IncrementFunctor = DefaultIncrement>
		void PushBack(float value);

		/// <summary>
		/// adds a string to the end of the array
		/// </summary>
		template <typename IncrementFunctor = DefaultIncrement>
		void PushBack(const std::string& value);

		/// <summary>
		/// adds a vector to the end of the array
		/// </summary>
		template <typename IncrementFunctor = DefaultIncrement>
		void PushBack(const glm::vec4& value);

		/// <summary>
		/// adds a matrix to the end of the array
		/// </summary>
		template <typename IncrementFunctor = DefaultIncrement>
		void PushBack(const glm::mat4& value);

		/// <summary>
		/// adds an RTTI pointer to the end of the array
		/// </summary>
		template <typename IncrementFunctor = DefaultIncrement>
		void PushBack(RTTI* const value);

		/// <summary>
		/// removes the final value of the array
		/// </summary>
		void PopBack();

		/// <summary>
		/// returns the index of a given value
		/// one overlaod for each datum type
		/// </summary>
		/// <param name="value">the value to be found</param>
		/// <returns>the index of the value</returns>
		size_t IndexOf(int value) const;
		size_t IndexOf(float value) const;
		size_t IndexOf(const std::string& value) const;
		size_t IndexOf(const glm::vec4& value) const;
		size_t IndexOf(const glm::mat4& value) const;
		size_t IndexOf(const Scope& value) const;
		size_t IndexOf(RTTI*& value) const;

		/// <summary>
		/// returns a value at the given index
		/// </summary>
		template <typename T>
		T& Get(size_t index = 0);

		/// <summary>
		/// cosnt version of get
		/// returns a value at the given index
		/// </summary>
		template <typename T>
		const T& Get(size_t index = 0) const;

		/// <summary>
		/// sets the value at the given index to the passed in value
		/// one overload for each datum type
		/// </summary>
		/// <param name="value">the value to be set</param>
		/// <param name="index">the index to be set at</param>
		void Set(int value, size_t index = 0);
		void Set(float value, size_t index = 0);
		void Set(const std::string& value, size_t index = 0);
		void Set(const glm::vec4& value, size_t index = 0);
		void Set(const glm::mat4& value, size_t index = 0);
		void Set(Scope& value, size_t index = 0);
		void Set(RTTI*& value, size_t index = 0);

		/// <summary>
		/// sets a vale at a given index based on a string
		/// </summary>
		/// <param name="toSet">the value to be set</param>
		/// <param name="index">the index to be set at</param>
		template<typename T>
		void SetFromString(std::string toSet, size_t index = 0);

		template<typename T>
		void PushBackFromString(std::string toSet);

		/// <summary>
		/// returns the first value in the datum
		/// </summary>
		template <typename T>
		T& Front();

		/// <summary>
		/// cosnt version of front
		/// retrns the first value in the datum
		/// </summary>
		template <typename T>
		const T& Front() const;

		/// <summary>
		/// returns the final value in the datum
		/// </summary>
		template <typename T>
		T& Back();

		/// <summary>
		/// const version of back
		/// returns the final value in the datum
		/// </summary>
		template <typename T>
		const T& Back() const;

		/// <summary>
		/// removes the given value from the datum
		/// one overload for each datum type
		/// </summary>
		/// <param name="toRemove">the value to be removed</param>
		void Remove(int toRemove);
		void Remove(float toRemove);
		void Remove(const std::string& toRemove);
		void Remove(const glm::vec4& toRemove);
		void Remove(const glm::mat4& toRemove);
		void Remove(const Scope& toRemove);
		void Remove(RTTI* toRemove);

		/// <summary>
		/// removes a value at a given index
		/// </summary>
		/// <param name="index">the index to remove at</param>
		void RemoveAt(size_t index);

		/// <summary>
		/// returns a string made of a value at a given index
		/// </summary>
		/// <param name="index">the index to make into a string</param>
		/// <returns>the new string</returns>
		std::string ToString(size_t index = 0);

		/// <summary>
		/// sets the storage externally
		/// sets the pointer passed in to be this datums data, and sets the size
		/// one overload for each datum type
		/// </summary>
		/// <param name="arrayPtr">the array to be made the datum's data</param>
		/// <param name="size">the size of the array</param>
		void SetStorage(int* arrayPtr, size_t size);
		void SetStorage(float* arrayPtr, size_t size);
		void SetStorage(std::string* arrayPtr, size_t size);
		void SetStorage(glm::vec4* arrayPtr, size_t size);
		void SetStorage(glm::mat4* arrayPtr, size_t size);
		void SetStorage(RTTI** arrayPtr, size_t size);

		inline static const std::map<const std::string, Datum::DatumTypes> m_TypeMap =
		{
			{"integer", DatumTypes::INTEGER},
			{"float", DatumTypes::FLOAT},
			{"string", DatumTypes::STRING},
			{"vector", DatumTypes::VECTOR},
			{"matrix", DatumTypes::MATRIX},
			{"table", DatumTypes::TABLE}
		};


		/// <summary>
		/// returns whether or not the datum is stored externally
		/// </summary>
		/// <returns></returns>
		bool IsExternal() const;

	private:
		/// <summary>
		/// adds a scope to the end of the array
		/// </summary>
		template <typename IncrementFunctor = DefaultIncrement>
		void PushBack(Scope& value);

		/// <summary>
		/// helper function for the shared code in pushback
		/// sets the type, reserves if necessary, and increments the size
		/// </summary>
		template <typename IncrementFunctor = DefaultIncrement>
		void PushBackPrep(DatumTypes type);

		/// <summary>
		/// helper function that sets the storage to be external
		/// </summary>
		/// <param name="arrayPtr">the pointer to the array, casted to void</param>
		/// <param name="size">the size of the array being passed in</param>
		/// <param name="type">the type the datum is to be set to</param>
		void SetStorage(void* arrayPtr, size_t size, DatumTypes type);

		/// <summary>
		/// helper function to check if the types match
		/// </summary>
		/// <param name="type">the type to be checked</param>
		/// <exception cref="runtime_error">throws an exception if the types do not match</exception>
		void TypeCheck(DatumTypes type) const;

		/// <summary>
		/// helper function to make sure an index is within the datum's bounds
		/// </summary>
		/// <param name="index">the index to be checked</param>
		/// <exception cref="runtime_error">throws an exception if the index is out of bounds</exception>
		void BoundsCheck(size_t index) const;
		
		/// <summary>
		/// helper function to make sure a datum is internally stored
		/// </summary>
		/// <exception cref="runtime_error">throws an exception if the datum is externally stored</exception>
		void ExternalCheck() const;

		/// <summary>
		/// the array of pointers to the data
		/// stored as a union so that it may be manipulated without prior knowledge of the type
		/// </summary>
		union DatumValues
		{
			char* c; //bytes
			int* i; //int
			float* f; //float
			std::string* s; //string
			glm::vec4* v; //vector
			glm::mat4* m; //matrix
			RTTI** p; //pointer
			Scope** t; //table
			void* vp = nullptr; //void pointer
		};

		/// <summary>
		/// array of the sizes of each data type
		/// </summary>
		inline static const size_t m_SizeMap[static_cast<int>(DatumTypes::END) + 1] =
		{
			sizeof(int), //int
			sizeof(float), //float
			sizeof(std::string), //string
			sizeof(glm::vec4), //vector
			sizeof(glm::mat4), //matrix
			sizeof(Scope*), //table
			sizeof(RTTI*), //pointer
		};	

		/// <summary>
		/// functions to default instantiate each data type
		/// </summary>
		void CreateInteger(size_t index);
		void CreateFloat(size_t index);
		void CreateString(size_t index);
		void CreateVector(size_t index);
		void CreateMatrix(size_t index);
		void CreateScope(size_t index);
		void CreatePointer(size_t index);

		/// <summary>
		/// functions to compare the datum types
		/// </summary>
		bool DefaultCompare(const Datum& toCompare) const;
		bool CompareStringDatum(const Datum& toCompare) const;
		bool ComparePtrDatum(const Datum& toCompare) const; 

		/// <summary>
		/// array of functions that default instantiate the data types
		/// </summary>
		using CreateDefaultFunction = void(Datum::*)(size_t index);
		inline static const CreateDefaultFunction m_CreateFunctions[static_cast<int>(DatumTypes::END) + 1] =
		{
			&Datum::CreateInteger, //int
			&Datum::CreateFloat, //float
			&Datum::CreateString, //string
			&Datum::CreateVector, //vector
			&Datum::CreateMatrix, //matrix
			&Datum::CreateScope, //table
			&Datum::CreatePointer, //pointer
		};

		/// <summary>
		/// array of functions that compare each datum type
		/// </summary>
		using CompareFunctions = bool(Datum::*)(const Datum& toCompare) const;
		inline static const CompareFunctions m_CompareFunctions[static_cast<int>(DatumTypes::END) + 1] =
		{
			&Datum::DefaultCompare, //int
			&Datum::DefaultCompare, //float
			&Datum::CompareStringDatum, //string
			&Datum::DefaultCompare, //vector
			&Datum::DefaultCompare, //matrix
			&Datum::ComparePtrDatum, //table
			&Datum::ComparePtrDatum, //pointer
		};

		/// <summary>
		/// the data type of the datum
		/// </summary>
		DatumTypes m_Type = DatumTypes::UNKNOWN;

		/// <summary>
		/// the number of elements in the datum
		/// </summary>
		size_t m_Size = 0;

		/// <summary>
		/// the number of elements the datum can hold
		/// </summary>
		size_t m_Capacity = 0;

		/// <summary>
		/// the data the datum stores
		/// </summary>
		DatumValues	m_Data;

		/// <summary>
		/// whether or not the datum is stored externally
		/// </summary>
		bool m_IsExternal = false;
	};
}

#include "Datum.inl"

