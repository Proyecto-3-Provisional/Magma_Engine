#pragma once

#ifdef MAGMAENGINE_EXPORTS
#define MAGMAENGINE_API __declspec(dllexport)
#else
#define MAGMAENGINE_API __declspec(dllimport)
#endif

#include <string>
#include <map>

#include <EC/component.h>

#include <singleton.h>

namespace magma_engine
{
	class Factory;

	class MAGMAENGINE_API FactoryManager : public Singleton<FactoryManager>
	{
	public:
		~FactoryManager();
		// Busca la factoría en el mapa, si la encuentra, crea el componente
		Component* findAndCreate(const std::string& name, Entity* ent = nullptr);
		// Añade las factorías en un mapa de strings en factorías
		void addFactory(const std::string& name, Factory* fact);
	private:
		std::map<std::string, Factory*> map_;
		template <typename T>
		Component* createComponent() { return new T; };
	};
}


