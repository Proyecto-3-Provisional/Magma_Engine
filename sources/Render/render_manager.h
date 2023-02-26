#pragma once

#include "render_manager_context.h"
#include "graphical_object.h"

class RenderManager : public RenderManagerContext
{
#define NUM_CREWMATES 16 // Colores de tripulantes
public:
	explicit RenderManager(); // new -> setup()
	virtual ~RenderManager(); // delete -> shutdown()

	// Ejemplo de movimiento
	void rotateObjects(float deltaTime);

	// Crear objeto
	bool addObject(std::string key, GraphicalObject* parent,
		std::string mesh, std::string material);
	// Obtener objeto
	GraphicalObject* getObject(std::string key);
	// Marcar objeto para destrucción segura (control de cuándo)
	void sunsetObject(GraphicalObject* gO);
	bool sunsetObject(std::string key);
	// Destruir objeto
	bool removeObject(GraphicalObject* gO);
	bool removeObject(std::string key);
	// Destruir todos los objetos (asegurarse al final)
	void removeObjects();
	// Destruir aquellos objetos que fueron marcados previamente
	bool refreshObjects();

protected:
	// Objetos nuestros del mundo gráfico
	std::unordered_map<std::string, GraphicalObject*> sceneObjects;
	std::list<GraphicalObject*> sceneObjectsToRemove;

	// Preparar
	virtual void setup();

	// Conformar escena
	virtual void setupScene();

	// Cerrar
	virtual void shutdown();

	// Reaccionar a eventos de entrada
	virtual void pollEvents();

	// Punteros
	Ogre::SceneManager* mSM = nullptr;
	Ogre::SceneNode* mLightNode = nullptr;
	Ogre::SceneNode* mCamNode = nullptr;
	Ogre::SceneNode* mCubeNode = nullptr;
	Ogre::SceneNode* mPlaneNode = nullptr;

	Ogre::SceneNode* mCrewNode = nullptr;
	Ogre::Entity* mCrew[NUM_CREWMATES];

	// Objeto Gráfico (nueva clase) a rotar
	GraphicalObject* rotatingGraphicalObjectBody;

private:
	// Interruptor
	bool keydown;
	// Control de la velocidad de rotación
	float rotationVelocity;
	// Colores de tripulantes
	const Ogre::String crew_colors[NUM_CREWMATES]{
		"amongus_red",
		"amongus_brown",
		"amongus_orange",
		"amongus_yellow",
		"amongus_lime",
		"amongus_green",
		"amongus_aqua",
		"amongus_cyan",
		"amongus_blue",
		"amongus_purple",
		"amongus_magenta",
		"amongus_pink",
		"amongus_white",
		"amongus_grey_light",
		"amongus_grey_dark",
		"amongus_black"
	};
};
