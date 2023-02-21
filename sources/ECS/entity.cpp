#include "entity.h"

#include "component.h"
//#include "entity_manager.h"

void Entity::setContext(EntityManager* mngr) {

}

void Entity::update(){
	/*std::vector<Component*> v;
	Component* c;
	c->update();

	v.push_back(c)
	v[1]->update();*/

	auto n = currCmps_.size();
	for (auto i = 0u; i < n; i++)
		currCmps_[i]->update();
}

void Entity::render() {
	auto n = currCmps_.size();
	for (auto i = 0u; i < n; i++)
		currCmps_[i]->render();
}

//template<typename T, typename ...Ts>
//void Entity::addComponent(Ts &&... args) {
//	{
//
//		//<<<
//		/*constexpr cmpId_type cId = T::id;
//		assert(cId < ecs::maxComponentId);*/
//
//		// delete the current component, if any
//		//
//		removeComponent<T>();
//
//		// create, initialise and install the new component
//		//
//		Component* c = new T(std::forward<Ts>(args)...);
//		c->setContext(this, mngr_);
//		c->initComponent();
//		//cmps_[cId] = c; //<<<
//		currCmps_.push_back(c);
//
//		// return it to the user so i can be initialised if needed
//		return static_cast<T*>(c);
//	}
//}
