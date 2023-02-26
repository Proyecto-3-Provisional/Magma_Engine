#include "transform.h"
#include "entity.h"
#include "OgreSceneNode.h"

void Transform::update()
{
	//ent_->getOgreNode()->setPosition(x, y, z);
	pos = pos + vel;
	std::cout << getPos().getX() << '\n';
}
