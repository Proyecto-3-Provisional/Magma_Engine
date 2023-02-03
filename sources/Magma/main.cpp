#include <iostream>
#include "Ogro.h"

int main(int argc, char const** argv) {
	std::cout << "Hola Mundo\n";

	Ogro* miOgro = new Ogro();
	miOgro->construye();
	miOgro->destruye();

	return 0;
}
