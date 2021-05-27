#include "pch.h"
#include "Factory.h"

namespace FieaGameEngine
{
	template<typename T>
	inline const Factory<T>* const Factory<T>::Find(const std::string& className)
	{
		auto it = s_FactoryMap.Find(className);
		return (it != s_FactoryMap.end()) ? it->second : nullptr;
	}

	template<typename T>
	inline T* Factory<T>::Create(const std::string& className)
	{
		const Factory<T>* const factory = Find(className);
		return (factory != nullptr) ? factory->Create() : nullptr;
	}

	template<typename T>
	inline void Factory<T>::Add(const Factory<T>& factory)
	{
		if (s_FactoryMap.ContainsKey(factory.ClassName()))
		{
			throw std::runtime_error("Factory is already registered");
		}

		s_FactoryMap.Insert(make_pair(factory.ClassName(), &factory));
	}

	template<typename T>
	void Factory<T>::Remove(const Factory& factory)
	{
		s_FactoryMap.Remove(factory.ClassName());
	}
}