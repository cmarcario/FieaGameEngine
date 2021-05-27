#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Datum.h"

namespace FieaGameEngine
{
	template<>
	struct Datum::TypeMap<Datum::DatumTypes::INTEGER>
	{
		using DatumType = int;
	};

	template<>
	struct Datum::TypeMap<Datum::DatumTypes::FLOAT>
	{
		using DatumType = float;
	};

	template<>
	struct Datum::TypeMap<Datum::DatumTypes::STRING>
	{
		using DatumType = std::string;
	};

	template<>
	struct Datum::TypeMap<Datum::DatumTypes::VECTOR>
	{
		using DatumType = glm::vec4;
	};

	template<>
	struct Datum::TypeMap<Datum::DatumTypes::MATRIX>
	{
		using DatumType = glm::mat4;
	};

	template<>
	struct Datum::TypeMap<Datum::DatumTypes::POINTER>
	{
		using DatumType = void*;
	};
}