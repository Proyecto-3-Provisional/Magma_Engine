// Samir Genaim (modificado mas o menos en funcion de nuestras necesidades)

#pragma once

#include <cstdint>
#include <EC/ec.h>

// Definimos los nombres de los mensajes, son accesibles desde nuestros componentes, por ejemplo en transform.h, pitch(). 
// Para recibir, usar como ejemplo mesh recieve 
using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_OBJECT_ROTATED, // rotamos en alguno de los 3 ejes x, y o z
	_m_OBJECT_LOOKAT // rotamos para mirar a una posicion
};


struct Message {
	msgId_type id;

	// si usamos union ahorraremos memoria, pero solo usaremos tipos
	// primitivos, de otra manera se necesitarán definir constructores
	// casi en todas partes(no usar Vector3D, por ejemplo, poner 3 float
	// en su lugar)
	union {

		//_m_OBJECT_ROTATED, para rotar objeto sobre un eje
		struct {
			float deg;
			char axis;
		} object_rotated_data;
		 
		//_m_OBJECT_LOOKAT, para hacer que un objeto rote y mire a un punto xyz
		struct {
			float x;
			float y;
			float z;
		} object_lookedat_data;
	};
};
