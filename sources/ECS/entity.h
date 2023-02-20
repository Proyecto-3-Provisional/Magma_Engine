// This file is part of the course TPV2@UCM - Samir Genaim (modified to some extent or another)

#pragma once

#include "Component.h"

#include <array>
#include <vector>

namespace magma {

	//entity va a actuar como una coleccion de componentes
	class Entity {
	public:
		Entity() :
			mngr_(nullptr), /*cmps_(),*/ currCmps_(), alive_() {
			currCmps_.reserve(10/*ecs::maxComponentId*/);
		}
		virtual ~Entity() {
			for (auto c : currCmps_) {
				delete c;
			}
		};
		inline void setContext(EntityManager* mngr);
		inline bool isAlive();
		inline void setAlive(bool alive);

		inline void update() {
			auto n = currCmps_.size();
			for (auto i = 0u; i < n; i++)
				currCmps_[i]->update();
		}

		inline void render() {
			auto n = currCmps_.size();
			for (auto i = 0u; i < n; i++)
				currCmps_[i]->render();
		}

		//<<< significa editado/comentado para no usar Id's de componentes

		// Adds a component. It receives the type T (to be created), and the
		// list of arguments (if any) to be passed to the constructor.
		// The component identifier 'cId' is taken from T::id.
		template<typename T, typename ...Ts>
		inline T* addComponent(Ts &&... args) {

			//<<<
			/*constexpr cmpId_type cId = T::id;
			assert(cId < ecs::maxComponentId);*/

			// delete the current component, if any
			//
			removeComponent<T>();

			// create, initialise and install the new component
			//
			Component* c = new T(std::forward<Ts>(args)...);
			c->setContext(this, mngr_);
			c->initComponent();
			//cmps_[cId] = c; //<<<
			currCmps_.push_back(c);

			// return it to the user so i can be initialised if needed
			return static_cast<T*>(c);
		}

		//hay que encontrar una forma de quitar un componente sin usar su Id(seguramente facil simplemente con su tipo?)
		// Removes the components at position T::id.
		template<typename T>
		inline void removeComponent() {

			//<<<
			/*constexpr cmpId_type cId = T::id;
			assert(cId < ecs::maxComponentId);*/

			//if (cmps_[cId] != nullptr) {

			//	// find the element that is equal tocmps_[cId] (returns an iterator)
			//	//
			//	auto iter = std::find(currCmps_.begin(), currCmps_.end(),
			//		cmps_[cId]);

			//	// must have such a component
			//	assert(iter != currCmps_.end());

			//	// and then remove it
			//	currCmps_.erase(iter);

			//	// destroy it
			//	//
			//	delete cmps_[cId];

			//	// remove the pointer
			//	//
			//	cmps_[cId] = nullptr;
			//}
		}

		//cambiar a que sea sin Id
		// Returns the component that corresponds to position T::id, casting it
		// to T*. The casting is done just for ease of use, to avoid casting
		// outside.
		template<typename T>
		inline T* getComponent() {
			//<<<
			/*constexpr cmpId_type cId = T::id;
			assert(cId < ecs::maxComponentId);

			return static_cast<T*>(cmps_[cId]);*/
		}

		//cambiar a que sea sin Id
		// return true if there is a component with identifier T::id
		template<typename T>
		inline bool hasComponent() {
			//<<<
			/*constexpr cmpId_type cId = T::id;
			assert(cId < ecs::maxComponentId);

			return cmps_[cId] != nullptr;*/
		}

		//// returns the entity's group 'gId'
		////
		//inline ecs::grpId_type groupId() {
		//	return gId_;
		//}
	private:
		bool alive_;
		Manager* mngr_;
		std::vector<Component*> currCmps_;
		//desde el juego habria que indicar maxComponentId(cuandtos comps lleva). Por ahora ponemos un maximo de 10. Generalmente indicaria el tipo 1 siempre Transform... no tenemos eso
		//std::array<Component*, 10/*ecs::maxComponentId*/> cmps_;
	};
}



