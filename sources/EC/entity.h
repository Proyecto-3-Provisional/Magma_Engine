// Samir Genaim (modificado mas o menos en funcion de nuestras necesidades)

#pragma once

#include <array>
#include <vector>

#include <EC/component.h>
#include <unordered_map>

namespace magma_engine
{
	class Entity {
	public:
		Entity();
		virtual ~Entity();

		// Borramos los constructores de copia y asignacion porque no queda claro como copiar componentes
		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;

		void setAlive(bool alive_);

		inline bool isAlive() {
			return alive;
		}

		// Añade un componente a la entidad 'e'. Recibe, ademas del tipo T, los argumentos(si necesita) 
		// para pasarle a la constructora
		template<typename T, typename ...Ts>
		T* addComponent(Ts &&... args) {
			removeComponent<T>();

			std::string tipo = typeid(T).name();

			Component* c = new T(std::forward<Ts>(args)...);
			c->setContext(this);
			cmps.insert({ tipo, c });

			return static_cast<T*>(c);
		}

		// Elimina el componente de tipo T de la entidad 'e' 
		template<typename T>
		void removeComponent() {
			std::string tipo = typeid(T).name();

			auto it = cmps.find(tipo);
			if (it != cmps.end()) { // Ha encontrado el componente
				//Eliminarlo
				delete it->second;
				it->second = nullptr;

				cmps.erase(tipo);
			}
		}

		// Devuelve un puntero al componente T de la entidad 'e'
		template<typename T>
		T* getComponent() {
			std::string tipo = typeid(T).name();

			auto it = cmps.find(tipo);
			if (it != cmps.end()) { // Ha encontrado el componente
				return static_cast<T*>(it->second);
			}

			return nullptr;
		}

		// Devuelve true si la entidad 'e' tiene el componente T
		template<typename T>
		bool hasComponent() {
			std::string tipo = typeid(T).name();

			auto it = cmps.find(tipo);
			if (it != cmps.end()) { // Ha encontrado el componente
				return true;
			}

			return false;
		}

		void update(float deltaTime);

		void render();

		// Manda un mensaje 'm' a todos los componentes de la entidad. 'delay' indica si deberia
		// mandarse inmediatamente o mas tarde cuando llamamos a flushMessages
		void send(const Message& m, bool delay = false); //por ahora no tenemos flush de mensajes implementado, dejar elay a false

		std::vector<Component*> getAllCmps();

	private:
		std::unordered_map<std::string, Component*> cmps;

		bool alive;

		std::vector<Message> msgs_;
		std::vector<Message> msgs_aux_;
	};
}

