// Samir Genaim (modificado mas o menos en funcion de nuestras necesidades)

#pragma once

/* COMO USAR MENSAJES:

	1) En messages_defs.h escribimos, dentro del struct msgId, el nombre del mensaje que queremos mandar(seguir plantilla de los ya escritos)

	2) Si queremos pasar informacion por el mensaje, dentro del union del struct Message, crear un struct con un nombre que siga la plantilla de
	los que ya estan. Nota: solo se permiten tipos basicos, para pasar la informacion de nuestro Vector3D, por ejemplo, tendrias que pasar 3 float.

	3) Los mensajes los mandan COMPONENTES, y la entidad se encarga de que todos los demas componentes de la entidad se enteren. Para mandar uno,
	seguir este ejemplo creado en la funcion pitch de transform.cpp:

	Message m;
	m.id = _m_OBJECT_ROTATED;			//nombre asignado en el paso 1
	m.object_rotated_data = {deg, 'x'}; //la informacion que creamos en el struct del paso 2
	ent->send(m);					//la entidad asociada manda el mensaje creado

	4) Para recibir el mensaje: Los componentes tienen un metodo virtual recieve(). Para cambiarlo redefinimos en el componente con el metodo 
	"void recieve(const Message&) override;". Para indicar que hacer con cada mensaje, seguir este ejemplo de mesh.cpp:

	void Mesh::recieve(const Message& m)
	{
		switch (m.id)
		{
			case _m_OBJECT_ROTATED:													//el mensaje que quieres recibir
				rotate(m.object_rotated_data.deg, m.object_rotated_data.axis);		//lo que quieres que haga al recibirlo
			default:
				break;
		}
	}

	5) Algunas notas extra
		Se coloca la definición de "Message" en un archivo separado para
		evitar dependencias circulares con ec.h

		No los incluimos en el namespace ec para evitar escribir el
		prefijo ec:: en las clases de usuario

		Por defecto el struct Message es

		struct Message {
			 uint8_t id;
		}
*/

#if __has_include("messages_defs.h")
#include "messages_defs.h"
#else
#include <cstdint>
struct Message {
	uint8_t id;
};
#endif
