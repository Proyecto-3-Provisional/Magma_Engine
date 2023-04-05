#pragma once

class EntityManager;

class Scene
{
public:
	Scene();
	~Scene();

	void update(float deltaTime);

	bool loadScene();
};

