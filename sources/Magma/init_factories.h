#pragma once
#include "factory.h"

class ec::Component;

class TransformFactory : public Factory
{
public:
	ec::Component* createComponent(ec::Entity* e);
};

class RigidbodyFactory : public Factory
{
public:
	ec::Component* createComponent(ec::Entity* e);
};

class MeshFactory : public Factory
{
public:
	ec::Component* createComponent(ec::Entity* e);
};

void setUpFactories();