#include "test_axl_mov.h"

void TestAxlMov::update()
{
	if (abs(this->getPos().getX()) > 500)
		this->getVel() = this->getVel() * -1;

	Transform::update();
}
