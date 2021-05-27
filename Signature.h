#pragma once
#include <string>
#include "Datum.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Signature class
	/// stores the data for a class's members
	/// holds the name, the type, its size in elements, and the offset from this in memory
	/// </summary>
	class Signature
	{
		using DatumType = Datum::DatumTypes;
	public:
		/// <summary>
		/// constructor for signatures
		/// takes in the attributes for a certain member and stores them
		/// </summary>
		/// <param name="name"></param>
		/// <param name="type"></param>
		/// <param name="size"></param>
		/// <param name="offset"></param>
		Signature(std::string name, DatumType type, size_t size, size_t offset);

		/// <summary>
		/// the attributes name
		/// </summary>
		std::string m_Name;

		/// <summary>
		/// the attributes type
		/// </summary>
		DatumType m_Type;

		/// <summary>
		/// the size of the attribute (in elements)
		/// </summary>
		size_t m_Size;

		/// <summary>
		/// its offset from this (in bytes)
		/// </summary>
		size_t m_Offset;
	};
}