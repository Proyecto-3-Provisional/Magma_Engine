#pragma once
#include "factory.h"

class ec::Component;

class TransformFactory : public Factory
{
public:
	ec::Component* createComponent(std::map<std::string, std::string> args, ec::Entity* e) override;
};

class RigidbodyFactory : public Factory
{
public:
	ec::Component* createComponent(std::map<std::string, std::string> args, ec::Entity* e) override;
};

class MeshFactory : public Factory
{
public:
	ec::Component* createComponent(std::map<std::string, std::string> args, ec::Entity* e) override;
};

void setUpFactories();