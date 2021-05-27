#pragma once
#include <string>
#include "HashMap.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Factory class
	/// Instantiates an object of a registered type
	/// Keeps track of the currently existent factories
	/// </summary>
	template <typename T>
	class Factory
	{
	public:
		/// <summary>
		/// returns the name of the class the factory instantiates as a string
		/// </summary>
		/// <returns>the name of the class the factory instantiates</returns>
		virtual const std::string& ClassName() const = 0;

		/// <summary>
		/// returns a new instance of the class that the factory instantiates
		/// </summary>
		/// <returns>a new instance of the class</returns>
		virtual T* Create() const = 0;

		/// <summary>
		/// finds a specific factory based on the name of the class that it instantiates
		/// </summary>
		/// <param name="className">the name of the class whose factory you want to find</param>
		/// <returns>the factory that instantiates that class</returns>
		static const Factory* const Find(const std::string& className);

		/// <summary>
		/// creates an instance of a class based upon its name
		/// </summary>
		/// <param name="className">the name of the class to instantiate</param>
		/// <returns>a pointer to the new object</returns>
		static T* Create(const std::string& className);

	protected:
		/// <summary>
		/// adds a factory to the map of factories
		/// </summary>
		/// <param name="factory">the factory to be added</param>
		static void Add(const Factory& factory);

		/// <summary>
		/// removes a factory from the map of factories
		/// </summary>
		/// <param name="factory">the factory to be removed</param>
		static void Remove(const Factory& factory);

	private:
		/// <summary>
		/// hashmap of the "registered" factories
		/// </summary>
		static inline HashMap<const std::string, const Factory* const> s_FactoryMap;
	};

	/// <summary>
	/// macro that creates a factory for a given class
	/// </summary>
#define ConcreteFactory(Product, AbstractProduct) \
	class Product##Factory final : public FieaGameEngine::Factory<AbstractProduct> \
	{ \
	public: \
		Product##Factory(){ Add(*this); }; \
		~Product##Factory() { Remove(*this); }; \
		const std::string& ClassName() const override { return s_ClassName; }; \
		AbstractProduct* Create() const override { return new Product(); }; \
	private: \
		inline static const std::string s_ClassName { std::string(#Product) }; \
	};
}

#include "Factory.inl"