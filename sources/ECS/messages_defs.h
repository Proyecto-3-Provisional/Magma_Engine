// Samir Genaim (modificado mas o menos en funcion de nuestras necesidades)

#pragma once

#include <cstdint>
#include "ec.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {
	//_m_STAR_EATEN, //
	//_m_CREATE_STARS
};


struct Message {
	msgId_type id;

	// si usamos union ahorraremos memoria, pero solo usaremos tipos
	// primitivos, de otra manera se necesitarán definir constructores
	// casi en todas partes

	union {

		//// _m_STAR_EATEN
		//struct {
		//	ecs::Entity* e;
		//} star_eaten_data;

		//// _m_CREATE_STARS
		//struct {
		//	unsigned int n;
		//} create_stars_data;

	};
};
