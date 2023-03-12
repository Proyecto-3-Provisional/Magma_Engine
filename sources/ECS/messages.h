// Samir Genaim (modificado mas o menos en funcion de nuestras necesidades)

#pragma once

/*
 * Se coloca la definición de "Message" en un archivo separado para
 * evitar dependencias circulares con ec.h
 * 
 * No los incluimos en el namespace ec para evitar escribir el
 * prefijo ec:: en las clases de usuario
 *
 * Por defecto el struct Message es
 *
 *  struct Message {
 *	   uint8_t id;
 *  }
 *
 */

#if __has_include("messages_defs.h")
#include "messages_defs.h"
#else
#include <cstdint>
struct Message {
	uint8_t id;
};
#endif
