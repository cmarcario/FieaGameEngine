#include "pch.h"
#include <glm/gtx/string_cast.hpp>
#include "Datum.h"
#include "DefaultIncrement.h"

using namespace glm;
using namespace std;

namespace FieaGameEngine
{
	Datum::Datum(DatumTypes type) : m_Type(type) {}

	Datum::Datum(const Datum& ToCopy) : m_Type(ToCopy.m_Type)
	{
		if (!ToCopy.m_IsExternal)
		{
			Reserve(ToCopy.m_Capacity);
			if (m_Type == DatumTypes::STRING)
			{
				m_Size = 0;
				for (size_t i = 0; i < ToCopy.m_Size; ++i)
				{
					PushBack(ToCopy.m_Data.s[i]);
				}
			}
			else
			{
				m_Size = ToCopy.m_Size;
				memcpy(m_Data.vp, ToCopy.m_Data.vp, ToCopy.m_Size * m_SizeMap[static_cast<int>(m_Type)]);
			}
		}
		else
		{
			m_Data.vp = ToCopy.m_Data.vp;
			m_Capacity = ToCopy.m_Capacity;
			m_Size = ToCopy.m_Size;
			m_IsExternal = true;
		}
	}

	Datum::Datum(Datum&& ToMove) noexcept : 
		m_Type(ToMove.m_Type), m_Size(ToMove.m_Size), m_Capacity(ToMove.m_Capacity), m_IsExternal(ToMove.m_IsExternal)
	{
		m_Data.vp = ToMove.m_Data.vp;

		ToMove.m_Type = DatumTypes::UNKNOWN;
		ToMove.m_Capacity = 0;
		ToMove.m_Size = 0;
		ToMove.m_Data.vp = nullptr;
		ToMove.m_IsExternal = false;
	}

	Datum& Datum::operator=(const Datum& ToCopy)
	{
		if (this != &ToCopy)
		{
			if (!m_IsExternal)
			{
				Clear();
			}

			if (!ToCopy.m_IsExternal)
			{
				m_Type = ToCopy.m_Type;

				if (m_Capacity < ToCopy.m_Capacity)
				{
					Reserve(ToCopy.m_Capacity);
				}

				if (m_Type == DatumTypes::STRING)
				{
					for (size_t i = 0; i < ToCopy.m_Size; ++i)
					{
						PushBack(ToCopy.m_Data.s[i]);
					}
				}
				else
				{
					m_Size = ToCopy.m_Size;
					memcpy(m_Data.vp, ToCopy.m_Data.vp, ToCopy.m_Size * m_SizeMap[static_cast<int>(m_Type)]);
				}
			}
			else
			{
				if (!m_IsExternal)
				{
					free(m_Data.vp);
				}
				m_Data.vp = ToCopy.m_Data.vp;
				m_Capacity = ToCopy.m_Capacity;
				m_Size = ToCopy.m_Size;
				m_IsExternal = true;
			}
		}

		return *this;
	}

	Datum& Datum::operator=(Datum&& ToMove) noexcept
	{
		if (this != &ToMove)
		{
			if (!m_IsExternal)
			{
				Clear();
				free(m_Data.vp);
			}

			m_Type = ToMove.m_Type;
			m_Size = ToMove.m_Size;
			m_Capacity = ToMove.m_Capacity;
			m_Data.vp = ToMove.m_Data.vp;
			m_IsExternal = ToMove.m_IsExternal;

			ToMove.m_Type = DatumTypes::UNKNOWN;
			ToMove.m_Capacity = 0;
			ToMove.m_Size = 0;
			ToMove.m_Data.vp = nullptr;
			ToMove.m_IsExternal = false;
		}

		return *this;
	}

	bool Datum::operator==(const Datum& toCompare) const
	{
		if ((m_Size != toCompare.m_Size) || (m_Type != toCompare.m_Type))
		{
			return false;
		}

		if (m_Size > 0)
		{
			CompareFunctions compareFunc = m_CompareFunctions[static_cast<int>(m_Type)];
			return (this->*compareFunc)(toCompare);
		}

		return true;
	}

	bool Datum::operator!=(const Datum& toCompare) const
	{
		return !(operator==(toCompare));
	}

#pragma region operator= overloads

	Datum& Datum::operator=(int value)
	{
		SetType(DatumTypes::INTEGER);
		Clear();
		
		if (m_IsExternal)
		{
			Set(value);
		}
		else
		{
			PushBack(value);
		}

		return *this;
	}

	Datum& Datum::operator=(float value)
	{
		SetType(DatumTypes::FLOAT);

		if (m_IsExternal)
		{
			Set(value);
		}
		else
		{
			Clear();
			PushBack(value);
		}

		return *this;
	}

	Datum& Datum::operator=(const std::string& value)
	{
		SetType(DatumTypes::STRING);

		if (m_IsExternal)
		{
			Set(value);
		}
		else
		{
			Clear();
			PushBack(value);
		}

		return *this;
	}

	Datum& Datum::operator=(const glm::vec4& value)
	{
		SetType(DatumTypes::VECTOR);
		
		if (m_IsExternal)
		{
			Set(value);
		}
		else
		{
			Clear();
			PushBack(value);
		}

		return *this;
	}

	Datum& Datum::operator=(const glm::mat4& value)
	{
		SetType(DatumTypes::MATRIX);
		
		if (m_IsExternal)
		{
			Set(value);
		}
		else
		{
			Clear();
			PushBack(value);
		}

		return *this;
	}

	Datum& Datum::operator=(Scope& value)
	{
		SetType(DatumTypes::TABLE);
		
		if (m_IsExternal)
		{
			Set(value);
		}
		else
		{
			Clear();
			PushBack(value);
		}

		return *this;
	}

	Datum& Datum::operator=(RTTI* value)
	{
		SetType(DatumTypes::POINTER);
		
		if (m_IsExternal)
		{
			Set(value);
		}
		else
		{
			Clear();
			PushBack(value);
		}

		return *this;
	}

#pragma endregion operator= overloads

	void Datum::SetType(DatumTypes type)
	{
		if (m_Type != DatumTypes::UNKNOWN && type != m_Type)
		{
			throw std::runtime_error("Type has already been set");
		}

		m_Type = type;
	}

	void Datum::Reserve(size_t capacity)
	{
		if (capacity > m_Capacity)
		{
			if (m_Type == DatumTypes::UNKNOWN)
			{
				throw std::runtime_error("Type has not been set");
			}

			void* data = realloc(m_Data.vp, capacity * m_SizeMap[static_cast<int>(m_Type)]);
			assert(data != nullptr);
			m_Data.vp = data;
			m_Capacity = capacity;
		}
	}

	void Datum::Resize(size_t size)
	{
		ExternalCheck();
		if (m_Type == DatumTypes::UNKNOWN)
		{
			throw std::runtime_error("Type has not been set");
		}

		if (size < m_Size)
		{
			if (m_Type == DatumTypes::STRING)
			{
				for (size_t i = size; i < m_Size; ++i)
				{
					m_Data.s[i].~string();
				}
			}
		}
		else
		{
			Reserve(size);

			CreateDefaultFunction createFunc = m_CreateFunctions[static_cast<int>(m_Type)];
			assert(createFunc != nullptr);

			for (size_t i = m_Size; i < size; ++i)
			{
				(this->*createFunc)(i);
			}
		}
		m_Size = size;
	}

	size_t Datum::Size() const
	{
		return m_Size;
	}

	size_t Datum::Capacity() const
	{
		return m_Capacity;
	}

	Datum::DatumTypes Datum::Type() const
	{
		return m_Type;
	}

	void Datum::PopBack()
	{
		ExternalCheck();
		if (m_Type == DatumTypes::STRING)
		{
			m_Data.s[m_Size - 1].~string();
		}
		--m_Size;
	}

	void Datum::RemoveAt(size_t index)
	{
		ExternalCheck();
		if (index < m_Size)
		{
			if (m_Type == DatumTypes::STRING)
			{
				m_Data.s[index].~string();
			}

			char* destination = m_Data.c + (index * m_SizeMap[static_cast<int>(m_Type)]);
			char* source = destination + m_SizeMap[static_cast<int>(m_Type)];
			size_t bytes = (m_Size - index) * m_SizeMap[static_cast<int>(m_Type)];
			memmove(destination, source, bytes);
			--m_Size;
		}
	}

	std::string Datum::ToString(size_t index)
	{
		std::string returnString;
		switch (m_Type)
		{
		case DatumTypes::INTEGER:
			returnString = std::to_string(m_Data.i[index]);
			break;
		case DatumTypes::FLOAT:
			returnString = std::to_string(m_Data.f[index]);
			break;
		case DatumTypes::STRING:
			returnString = m_Data.s[index];
			break;
		case DatumTypes::VECTOR:
			returnString = glm::to_string(m_Data.v[index]);
			break;
		case DatumTypes::MATRIX:
			returnString = glm::to_string(m_Data.m[index]);
			break;
		case DatumTypes::POINTER:
			returnString = m_Data.p[index]->ToString();
			break;
		case DatumTypes::UNKNOWN:
			returnString = "Datum type unknown";
			break;
		default:
			break;
		}

		return returnString;
	}

#pragma region IndexOf Overloads
	
	size_t Datum::IndexOf(int value) const
	{
		TypeCheck(DatumTypes::INTEGER);
		size_t index = 0;

		for (index; index < m_Size; ++index)
		{
			if (m_Data.i[index] == value)
			{
				break;
			}
		}

		return index;
	}

	size_t Datum::IndexOf(float value) const
	{
		TypeCheck(DatumTypes::FLOAT);
		size_t index = 0;

		for (index; index < m_Size; ++index)
		{
			if (m_Data.f[index] == value)
			{
				break;
			}
		}

		return index;
	}

	size_t Datum::IndexOf(const std::string& value) const
	{
		TypeCheck(DatumTypes::STRING);
		size_t index = 0;

		for (index; index < m_Size; ++index)
		{
			if (m_Data.s[index] == value)
			{
				break;
			}
		}

		return index;
	}

	size_t Datum::IndexOf(const glm::vec4& value) const
	{
		TypeCheck(DatumTypes::VECTOR);
		size_t index = 0;

		for (index; index < m_Size; ++index)
		{
			if (m_Data.v[index] == value)
			{
				break;
			}
		}

		return index;
	}
	
	size_t Datum::IndexOf(const glm::mat4& value) const
	{
		TypeCheck(DatumTypes::MATRIX);
		size_t index = 0;

		for (index; index < m_Size; ++index)
		{
			if (m_Data.m[index] == value)
			{
				break;
			}
		}

		return index;
	}

	size_t Datum::IndexOf(const Scope& value) const
	{
		TypeCheck(DatumTypes::TABLE);
		size_t index = 0;

		for (index; index < m_Size; ++index)
		{
			if (m_Data.t[index] == &value)
			{
				break;
			}
		}

		return index;
	}

	size_t Datum::IndexOf(RTTI*& value) const
	{
		TypeCheck(DatumTypes::POINTER);
		size_t index = 0;

		for (index; index < m_Size; ++index)
		{
			if (m_Data.p[index] == value)
			{
				break;
			}
		}

		return index;
	}

#pragma endregion IndexOf Overloads

#pragma region Remove Overloads

	void Datum::Remove(int toRemove)
	{
		ExternalCheck();
		TypeCheck(DatumTypes::INTEGER);
		size_t index = IndexOf(toRemove);
		RemoveAt(index);
	}

	void Datum::Remove(float toRemove)
	{
		ExternalCheck();
		TypeCheck(DatumTypes::FLOAT);
		size_t index = IndexOf(toRemove);
		RemoveAt(index);
	}

	void Datum::Remove(const std::string& toRemove)
	{
		ExternalCheck();
		TypeCheck(DatumTypes::STRING);
		size_t index = IndexOf(toRemove);
		RemoveAt(index);
	}

	void Datum::Remove(const glm::vec4& toRemove)
	{
		ExternalCheck();
		TypeCheck(DatumTypes::VECTOR);
		size_t index = IndexOf(toRemove);
		RemoveAt(index);
	}

	void Datum::Remove(const glm::mat4& toRemove)
	{
		ExternalCheck();
		TypeCheck(DatumTypes::MATRIX);
		size_t index = IndexOf(toRemove);
		RemoveAt(index);
	}

	void Datum::Remove(const Scope& toRemove)
	{
		ExternalCheck();
		TypeCheck(DatumTypes::TABLE);
		size_t index = IndexOf(toRemove);
		RemoveAt(index);
	}

	void Datum::Remove(RTTI* toRemove)
	{
		ExternalCheck();
		TypeCheck(DatumTypes::POINTER);
		size_t index = IndexOf(toRemove);
		RemoveAt(index);
	}

#pragma endregion Remove Overloads

#pragma region Set Overloads

	void FieaGameEngine::Datum::Set(int value, size_t index)
	{
		TypeCheck(DatumTypes::INTEGER);
		BoundsCheck(index);
		m_Data.i[index] = value;
	}

	void FieaGameEngine::Datum::Set(float value, size_t index)
	{
		TypeCheck(DatumTypes::FLOAT);
		BoundsCheck(index);
		m_Data.f[index] = value;
	}

	void FieaGameEngine::Datum::Set(const std::string& value, size_t index)
	{
		TypeCheck(DatumTypes::STRING);
		BoundsCheck(index);
		m_Data.s[index].~string();
		m_Data.s[index] = value;
	}

	void FieaGameEngine::Datum::Set(const glm::vec4& value, size_t index)
	{
		TypeCheck(DatumTypes::VECTOR);
		BoundsCheck(index);

		m_Data.v[index] = value;
	}

	void FieaGameEngine::Datum::Set(const glm::mat4& value, size_t index)
	{
		TypeCheck(DatumTypes::MATRIX);
		BoundsCheck(index);

		m_Data.m[index] = value;
	}

	void Datum::Set(Scope& value, size_t index)
	{
		TypeCheck(DatumTypes::TABLE);
		BoundsCheck(index);

		m_Data.t[index] = &value;
	}

	void FieaGameEngine::Datum::Set(RTTI*& value, size_t index)
	{
		TypeCheck(DatumTypes::POINTER);
		BoundsCheck(index);

		m_Data.p[index] = value;
	}

#pragma endregion Set Overloads

#pragma region SetStorage Overloads
	void Datum::SetStorage(void* arrayPtr, size_t size, DatumTypes type)
	{
		if (m_Capacity > 0 && !m_IsExternal)
		{
			throw std::runtime_error("Memory has already been allocated internally for this datum.");
		}

		m_IsExternal = true;
		m_Data.vp = arrayPtr;
		m_Size = size;
		m_Capacity = size;
		m_Type = type;
	}

	void Datum::SetStorage(int* arrayPtr, size_t size)
	{
		SetStorage(reinterpret_cast<void*>(arrayPtr), size, DatumTypes::INTEGER);
	}

	void Datum::SetStorage(float* arrayPtr, size_t size)
	{
		SetStorage(reinterpret_cast<void*>(arrayPtr), size, DatumTypes::FLOAT);
	}

	void Datum::SetStorage(std::string* arrayPtr, size_t size)
	{
		SetStorage(reinterpret_cast<void*>(arrayPtr), size, DatumTypes::STRING);
	}

	void Datum::SetStorage(glm::vec4* arrayPtr, size_t size)
	{
		SetStorage(reinterpret_cast<void*>(arrayPtr), size, DatumTypes::VECTOR);
	}

	void Datum::SetStorage(glm::mat4* arrayPtr, size_t size)
	{
		SetStorage(reinterpret_cast<void*>(arrayPtr), size, DatumTypes::MATRIX);
	}

	bool Datum::IsExternal() const
	{
		return m_IsExternal;
	}

	void Datum::SetStorage(RTTI** arrayPtr, size_t size)
	{
		SetStorage(reinterpret_cast<void*>(arrayPtr), size, DatumTypes::POINTER);
	}

#pragma endregion SetStorage Overloads

	void Datum::TypeCheck(DatumTypes type) const
	{
		if (type != m_Type)
		{
			throw std::runtime_error("Incorrect type");
		}
	}

	void Datum::BoundsCheck(size_t index) const
	{
		if (index >= m_Size)
		{
			throw std::runtime_error("Index is out of bounds");
		}
	}

	void Datum::ExternalCheck() const
	{
		if (m_IsExternal)
		{
			throw std::runtime_error("This datum is stored externally");
		}
	}

	void Datum::Clear()
	{
		ExternalCheck();
		if (m_Type == DatumTypes::STRING)
		{
			for (size_t i = 0; i < m_Size; ++i)
			{
				m_Data.s[i].~string();
			}
		}

		m_Size = 0;
	}

#pragma region Create Functions
	inline void Datum::CreateInteger(size_t index)
	{
		new(m_Data.i + index)int(0);
	}

	inline void Datum::CreateFloat(size_t index)
	{
		new(m_Data.f + index)float(0);
	}

	inline void Datum::CreateString(size_t index)
	{
		new(m_Data.s + index)string();
	}

	inline void Datum::CreateVector(size_t index)
	{
		new(m_Data.v + index)vec4();
	}

	inline void Datum::CreateMatrix(size_t index)
	{
		new(m_Data.i + index)mat4();
	}

	void Datum::CreateScope(size_t index)
	{
		new(m_Data.t + index)Scope*();
	}

	inline void Datum::CreatePointer(size_t index)
	{
		new(m_Data.i + index)RTTI*(nullptr);
	}

#pragma endregion Create Functions

#pragma region Compare Functions

	bool Datum::DefaultCompare(const Datum& toCompare) const
	{
		int memResult = memcmp(m_Data.vp, toCompare.m_Data.vp, m_Size * m_SizeMap[static_cast<int>(m_Type)]);
		bool compareResult = (memResult == 0);
		
		return compareResult;
	}

	bool Datum::CompareStringDatum(const Datum& toCompare) const
	{
		bool compareResult = false;

		
		for (size_t i = 0; i < m_Size; ++i)
		{
			compareResult = m_Data.s[i] == toCompare.m_Data.s[i];
			
			if (!compareResult)
			{
				break;
			}
		}

		return compareResult;
	}

	bool Datum::ComparePtrDatum(const Datum& toCompare) const
	{
		bool compareResult = false;

		for (size_t i = 0; i < m_Size; ++i)
		{
			compareResult = m_Data.p[i]->Equals(toCompare.m_Data.p[i]);

			if (!compareResult)
			{
				break;
			}
		}
		

		return compareResult;
	}

#pragma endregion Compare Functions

	Datum::~Datum()
	{
		if (m_Capacity > 0 && !m_IsExternal)
		{
			Clear();

			free(m_Data.vp);
		}
	}
}