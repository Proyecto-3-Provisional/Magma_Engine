// This file is part of the course TPV2@UCM - Samir Genaim (modified to some extent or another)

#pragma once

class EntityManager;
struct Component;
//#include "component.h"
#include <array>
#include <vector>
#include <string>

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
	void setContext(EntityManager* mngr);
	inline bool isAlive() { return true; };
	void setAlive(bool alive){};

	void update();

	void render();

	// Adds a component. It receives the type T (to be created), and the
	// list of arguments (if any) to be passed to the constructor.
	// The component identifier 'cId' is taken from T::id.
	template<typename T, typename ...Ts>
	T* addComponent(Ts &&... args) {

		//constexpr cmpId_type cId = T::id;
		//assert(cId < ecs::maxComponentId);

		//// delete the current component, if any
		////
		//removeComponent<T>(std::string id);

		//// create, initialise and install the new component
		////
		Component* c = new T(std::forward<Ts>(args)...);
		//c->setContext(this, mngr_);
		//c->initComponent();
		////cmps_[cId] = c; //<<<
		//currCmps_.push_back(c);

		//// return it to the user so i can be initialised if needed
		return static_cast<T*>(c);
	}

	//hay que encontrar una forma de quitar un componente sin usar su Id
	// Removes the components at position T::id.
	template<typename T>
	void removeComponent() {

		/*auto iter = std::find(currCmps_.begin(), currCmps_.end(),
			currCmps_[]);

		for (auto i : currCmps_) {
			if(currCmps_[i].)
		}

		assert(iter != nullptr);

		currCmps_.erase(iter);*/

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
	EntityManager* mngr_;
	std::vector<Component*> currCmps_;
	//desde el juego habria que indicar maxComponentId(cuandtos comps lleva). Por ahora ponemos un maximo de 10. Generalmente indicaria el tipo 1 siempre Transform... no tenemos eso
	//std::array<Component*, 10/*ecs::maxComponentId*/> cmps_;
};




