#include "pch.h"
#include "DefaultIncrement.h"

namespace FieaGameEngine
{
	size_t DefaultIncrement::operator()(size_t size, size_t capacity) const
	{
		UNREFERENCED_LOCAL(size);

		return capacity * 2;
	}
}