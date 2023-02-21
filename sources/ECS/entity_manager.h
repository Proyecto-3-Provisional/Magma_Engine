#pragma once

#include <vector>

class Entity;

class EntityManager {
public:
	EntityManager();
	virtual ~EntityManager();

	Entity* addEntity();
	void refresh();
	void update();
	void render();
private:
	std::vector<Entity*> ents_;
};

