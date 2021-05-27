#include <glm/glm.hpp>
#include "Datum.h"

using namespace glm;
using namespace std;

namespace FieaGameEngine
{
	template <typename IncrementFunctor>
	void Datum::PushBackPrep(DatumTypes type)
	{
		ExternalCheck();

		SetType(type);

		if (m_Size == m_Capacity)
		{
			IncrementFunctor increment;
			size_t increaseBy = increment(m_Size, m_Capacity);

			size_t capacity = m_Capacity + std::max<size_t>(1, increaseBy);

			Reserve(capacity);
		}
		++m_Size;
	}

#pragma region PushBack Overloads
	template <typename IncrementFunctor>
	inline void Datum::PushBack(int value)
	{
		PushBackPrep<IncrementFunctor>(DatumTypes::INTEGER);
		new(m_Data.i + (m_Size - 1))int(value);
	}

	template <typename IncrementFunctor>
	inline void Datum::PushBack(float value)
	{
		PushBackPrep<IncrementFunctor>(DatumTypes::FLOAT);
		new(m_Data.f + (m_Size - 1))float(value);
	}

	template <typename IncrementFunctor>
	inline void Datum::PushBack(const std::string& value)
	{
		PushBackPrep<IncrementFunctor>(DatumTypes::STRING);
		new(m_Data.s + (m_Size - 1))string(value);
	}

	template <typename IncrementFunctor>
	inline void Datum::PushBack(const glm::vec4& value)
	{
		PushBackPrep<IncrementFunctor>(DatumTypes::VECTOR);
		new(m_Data.v + (m_Size - 1))vec4(value);
	}

	template <typename IncrementFunctor>
	inline void Datum::PushBack(const glm::mat4& value)
	{
		PushBackPrep<IncrementFunctor>(DatumTypes::MATRIX);
		new(m_Data.m + (m_Size - 1))mat4(value);
	}

	template<typename IncrementFunctor>
	inline void Datum::PushBack(Scope& value)
	{
		PushBackPrep<IncrementFunctor>(DatumTypes::TABLE);
		new(m_Data.t + (m_Size - 1))Scope* (&value);
	}

	template <typename IncrementFunctor>
	inline void Datum::PushBack(RTTI* const value)
	{
		PushBackPrep<IncrementFunctor>(DatumTypes::POINTER);
		new(m_Data.p + (m_Size - 1))RTTI*(value);
	}

#pragma endregion PushBack Overloads

#pragma region Get Templates
	template<>
	inline int& FieaGameEngine::Datum::Get<int>(size_t index)
	{
		TypeCheck(DatumTypes::INTEGER);
		BoundsCheck(index);

		return m_Data.i[index];
	} 

	template<>
	inline float& FieaGameEngine::Datum::Get<float>(size_t index)
	{
		TypeCheck(DatumTypes::FLOAT);
		BoundsCheck(index);

		return m_Data.f[index];
	}

	template<>
	inline std::string& FieaGameEngine::Datum::Get<std::string>(size_t index)
	{
		TypeCheck(DatumTypes::STRING);
		BoundsCheck(index);

		return m_Data.s[index];
	}

	template<>
	inline glm::vec4& FieaGameEngine::Datum::Get<glm::vec4>(size_t index)
	{
		TypeCheck(DatumTypes::VECTOR);
		BoundsCheck(index);

		return m_Data.v[index];
	}

	template<>
	inline glm::mat4& FieaGameEngine::Datum::Get<glm::mat4>(size_t index)
	{
		TypeCheck(DatumTypes::MATRIX);
		BoundsCheck(index);

		return m_Data.m[index];
	}

	template<>
	inline Scope& FieaGameEngine::Datum::Get<Scope>(size_t index)
	{
		TypeCheck(DatumTypes::TABLE);
		BoundsCheck(index);

		return *(m_Data.t[index]);
	}

	template<>
	inline RTTI*& FieaGameEngine::Datum::Get<RTTI*>(size_t index)
	{
		TypeCheck(DatumTypes::POINTER);
		BoundsCheck(index);

		return m_Data.p[index];
	}

#pragma endregion Get Templates

#pragma region Const Get Templates
	template<>
	inline const int& FieaGameEngine::Datum::Get<int>(size_t index) const
	{
		TypeCheck(DatumTypes::INTEGER);
		BoundsCheck(index);

		return m_Data.i[index];
	}

	template<>
	inline const float& FieaGameEngine::Datum::Get<float>(size_t index) const
	{
		TypeCheck(DatumTypes::FLOAT);
		BoundsCheck(index);

		return m_Data.f[index];
	}

	template<>
	inline const std::string& FieaGameEngine::Datum::Get<std::string>(size_t index) const
	{
		TypeCheck(DatumTypes::STRING);
		BoundsCheck(index);

		return m_Data.s[index];
	}

	template<>
	inline const glm::vec4& FieaGameEngine::Datum::Get<glm::vec4>(size_t index) const
	{
		TypeCheck(DatumTypes::VECTOR);
		BoundsCheck(index);

		return m_Data.v[index];
	}

	template<>
	inline const glm::mat4& FieaGameEngine::Datum::Get<glm::mat4>(size_t index) const
	{
		TypeCheck(DatumTypes::MATRIX);
		BoundsCheck(index);

		return m_Data.m[index];
	}

	template<>
	inline const Scope& FieaGameEngine::Datum::Get<Scope>(size_t index) const
	{
		TypeCheck(DatumTypes::TABLE);
		BoundsCheck(index);

		return *(m_Data.t[index]);
	}

	template<>
	inline RTTI* const& FieaGameEngine::Datum::Get<RTTI*>(size_t index) const
	{
		TypeCheck(DatumTypes::POINTER);
		BoundsCheck(index);

		return m_Data.p[index];
	}

#pragma endregion Const Get Templates

#pragma region Front Templates

	template<>
	inline int& Datum::Front<int>()
	{
		TypeCheck(DatumTypes::INTEGER);
		BoundsCheck(0);
		return m_Data.i[0];
	}

	template<>
	inline float& Datum::Front<float>()
	{
		TypeCheck(DatumTypes::FLOAT);
		BoundsCheck(0);
		return m_Data.f[0];
	}

	template<>
	inline std::string& Datum::Front<std::string>()
	{
		TypeCheck(DatumTypes::STRING);
		BoundsCheck(0);
		return m_Data.s[0];
	}

	template<>
	inline glm::vec4& Datum::Front<glm::vec4>()
	{
		TypeCheck(DatumTypes::VECTOR);
		BoundsCheck(0);
		return m_Data.v[0];
	}

	template<>
	inline glm::mat4& Datum::Front<glm::mat4>()
	{
		TypeCheck(DatumTypes::MATRIX);
		BoundsCheck(0);
		return m_Data.m[0];
	}

	template<>
	inline Scope& Datum::Front<Scope>()
	{
		TypeCheck(DatumTypes::TABLE);
		BoundsCheck(0);
		return *(m_Data.t[0]);
	}

	template<>
	inline RTTI*& Datum::Front<RTTI*>()
	{
		TypeCheck(DatumTypes::POINTER);
		BoundsCheck(0);
		return m_Data.p[0];
	}

#pragma endregion Front Templates

#pragma region Const Front Templates

	template<>
	inline const int& Datum::Front<int>() const
	{
		TypeCheck(DatumTypes::INTEGER);
		BoundsCheck(0);
		return m_Data.i[0];
	}

	template<>
	inline const float& Datum::Front<float>() const
	{
		TypeCheck(DatumTypes::FLOAT);
		BoundsCheck(0);
		return m_Data.f[0];
	}

	template<>
	inline const std::string& Datum::Front<std::string>() const
	{
		TypeCheck(DatumTypes::STRING);
		BoundsCheck(0);
		return m_Data.s[0];
	}

	template<>
	inline const glm::vec4& Datum::Front<glm::vec4>() const
	{
		TypeCheck(DatumTypes::VECTOR);
		BoundsCheck(0);
		return m_Data.v[0];
	}

	template<>
	inline const glm::mat4& Datum::Front<glm::mat4>() const
	{
		TypeCheck(DatumTypes::MATRIX);
		BoundsCheck(0);
		return m_Data.m[0];
	}

	template<>
	inline const Scope& Datum::Front<Scope>() const
	{
		TypeCheck(DatumTypes::TABLE);
		BoundsCheck(0);
		return *(m_Data.t[0]);
	}

	template<>
	inline RTTI* const& Datum::Front<RTTI*>() const
	{
		TypeCheck(DatumTypes::POINTER);
		BoundsCheck(0);
		return m_Data.p[0];
	}

#pragma endregion Const Front Templates

#pragma region Back Templates

	template<>
	inline int& Datum::Back<int>()
	{
		TypeCheck(DatumTypes::INTEGER);
		BoundsCheck(m_Size - 1);
		return m_Data.i[m_Size - 1];
	}

	template<>
	inline float& Datum::Back<float>()
	{
		TypeCheck(DatumTypes::FLOAT);
		BoundsCheck(m_Size - 1);
		return m_Data.f[m_Size - 1];
	}

	template<>
	inline std::string& Datum::Back<std::string>()
	{
		TypeCheck(DatumTypes::STRING);
		BoundsCheck(m_Size - 1);
		return m_Data.s[m_Size - 1];
	}

	template<>
	inline glm::vec4& Datum::Back<glm::vec4>()
	{
		TypeCheck(DatumTypes::VECTOR);
		BoundsCheck(m_Size - 1);
		return m_Data.v[m_Size - 1];
	}

	template<>
	inline glm::mat4& Datum::Back<glm::mat4>()
	{
		TypeCheck(DatumTypes::MATRIX);
		BoundsCheck(m_Size - 1);
		return m_Data.m[m_Size - 1];
	}

	template<>
	inline Scope& Datum::Back<Scope>()
	{
		TypeCheck(DatumTypes::TABLE);
		BoundsCheck(m_Size - 1);
		return *(m_Data.t[m_Size - 1]);
	}

	template<>
	inline RTTI*& Datum::Back<RTTI*>()
	{
		TypeCheck(DatumTypes::POINTER);
		BoundsCheck(m_Size - 1);
		return m_Data.p[m_Size - 1];
	}

#pragma endregion Back Templates

#pragma region Const Back Templates

	template<>
	inline const int& Datum::Back<int>() const
	{
		TypeCheck(DatumTypes::INTEGER);
		BoundsCheck(m_Size - 1);
		return m_Data.i[m_Size - 1];
	}

	template<>
	inline const float& Datum::Back<float>() const
	{
		TypeCheck(DatumTypes::FLOAT);
		BoundsCheck(m_Size - 1);
		return m_Data.f[m_Size - 1];
	}

	template<>
	inline const std::string& Datum::Back<std::string>() const
	{
		TypeCheck(DatumTypes::STRING);
		BoundsCheck(m_Size - 1);
		return m_Data.s[m_Size - 1];
	}

	template<>
	inline const glm::vec4& Datum::Back<glm::vec4>() const
	{
		TypeCheck(DatumTypes::VECTOR);
		BoundsCheck(m_Size - 1);
		return m_Data.v[m_Size - 1];
	}

	template<>
	inline const glm::mat4& Datum::Back<glm::mat4>() const
	{
		TypeCheck(DatumTypes::MATRIX);
		BoundsCheck(m_Size - 1);
		return m_Data.m[m_Size - 1];
	}

	template<>
	inline const Scope& Datum::Back<Scope>() const
	{
		TypeCheck(DatumTypes::TABLE);
		BoundsCheck(m_Size - 1);
		return *(m_Data.t[m_Size - 1]);
	}

	template<>
	inline RTTI* const& Datum::Back<RTTI*>() const
	{
		TypeCheck(DatumTypes::POINTER);
		BoundsCheck(m_Size - 1);
		return m_Data.p[m_Size - 1];
	}

#pragma endregion Const Back Templates

#pragma region SetFromString templates
	
	template<>
	inline void Datum::SetFromString<int>(std::string toSet, size_t index)
	{
		int value = stoi(toSet);
		Set(value, index);
	}

	template<>
	inline void Datum::SetFromString<float>(std::string toSet, size_t index)
	{
		float value = stof(toSet);
		Set(value, index);
	}

	template<>
	inline void Datum::SetFromString<string>(std::string toSet, size_t index)
	{
		Set(toSet, index);
	}

	template<>
	inline void Datum::SetFromString<glm::vec4>(std::string toSet, size_t index)
	{
		float float1;
		float float2;
		float float3;
		float float4;

		sscanf_s(toSet.c_str(), "vec4(%f, %f, %f, %f)", &float1, &float2, &float3, &float4);
		glm::vec4 newVec(float1, float2, float3, float4);
		Set(newVec, index);
	}

	template<>
	inline void Datum::SetFromString<glm::mat4>(std::string toSet, size_t index)
	{
		float float1, float2, float3, float4, float5, float6, float7, float8, float9, float10, float11, float12, float13, float14, float15, float16;

		sscanf_s(toSet.c_str(), "mat4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))", &float1, &float2, &float3, &float4, &float5, &float6, &float7, &float8, &float9, &float10, &float11, &float12, &float13, &float14, &float15, &float16);
		glm::mat4 newMat(float1, float2, float3, float4, float5, float6, float7, float8, float9, float10, float11, float12, float13, float14, float15, float16);
		Set(newMat, index);
	}

	template<>
	inline void Datum::SetFromString<RTTI*>(std::string toSet, size_t index)
	{
		UNREFERENCED_LOCAL(index);
		UNREFERENCED_LOCAL(toSet);
		throw std::runtime_error("RTTI* cannot be set from string");
	}

#pragma endregion SetFromString templates

#pragma region PushBackFromString templates

	template<>
	inline void Datum::PushBackFromString<glm::vec4>(std::string toSet)
	{
		float float1;
		float float2;
		float float3;
		float float4;

		sscanf_s(toSet.c_str(), "vec4(%f, %f, %f, %f)", &float1, &float2, &float3, &float4);
		glm::vec4 newVec(float1, float2, float3, float4);
		PushBack(newVec);
	}

	template<>
	inline void Datum::PushBackFromString<glm::mat4>(std::string toSet)
	{
		float float1, float2, float3, float4, float5, float6, float7, float8, float9, float10, float11, float12, float13, float14, float15, float16;

		sscanf_s(toSet.c_str(), "mat4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))", &float1, &float2, &float3, &float4, &float5, &float6, &float7, &float8, &float9, &float10, &float11, &float12, &float13, &float14, &float15, &float16);
		glm::mat4 newMat(float1, float2, float3, float4, float5, float6, float7, float8, float9, float10, float11, float12, float13, float14, float15, float16);
		PushBack(newMat);
	}

#pragma endregion PushBackFromString templates
}