// Samir Genaim (modificado mas o menos en funcion de nuestras necesidades)

#pragma once

#ifdef MAGMAENGINE_EXPORTS
#define MAGMAENGINE_API __declspec(dllexport)
#else
#define MAGMAENGINE_API __declspec(dllimport)
#endif

#include <vector>

#include <EC/entity.h>

namespace magma_engine
{
	class MAGMAENGINE_API EntityManager {
	public:
		EntityManager() {};
		virtual ~EntityManager();

		Entity* addEntity() {
			auto e = new Entity();
			e->setAlive(true);

			ents_.push_back(e);

			return e;
		}

		// Elimina las entidades muertas de las listas de grupos y las que ya no pertenecen a ningun grupo
		void refresh();

		void update(float deltaTime);
		void render();

		inline const auto& getEntities() {
			return ents_;
		}

	private:
		std::vector<Entity*> ents_;
	};
}

