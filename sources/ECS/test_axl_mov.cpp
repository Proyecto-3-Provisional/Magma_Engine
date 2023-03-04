#include "test_axl_mov.h"

void TestAxlMov::update(float deltaTime)
{
	// He cambiado el código anterior,
	// que al ser tan simple, en cocasiones hacía que
	// que el ajolote se atascase al empezar el programa
	// si la velocidad establecida era alta
	// (a veces hasta en mitad de ejecución quedaba
	// atascado al final de su recorrido, habiendo
	// establecido una velocidad razonable)		-Javier
	if (this->getPos().getX() > 500)
		if (this->getVel().getX() > 0)
			this->getVel() = this->getVel() * -1;
	if (this->getPos().getX() < -500)
		if (this->getVel().getX() < 0)
			this->getVel() = this->getVel() * -1;

	Transform::update(deltaTime);
}
