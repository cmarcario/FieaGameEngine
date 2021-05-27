#include "pch.h"
#include "Signature.h"

namespace FieaGameEngine
{
	Signature::Signature(std::string name, DatumType type, size_t size, size_t offset) :
		m_Name(name), m_Type(type), m_Size(size), m_Offset(offset) { }
}