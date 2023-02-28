#pragma once

#include "render_manager_context.h"
#include "graphical_object.h"

class RenderManager : public RenderManagerContext
{
public:
	explicit RenderManager(); // new -> setup()
	virtual ~RenderManager(); // delete -> shutdown()

	// Crear objeto
	GraphicalObject* addObject(std::string key, GraphicalObject* parent,
		std::string mesh, std::string material);

	// Obtener objeto
	GraphicalObject* getObject(std::string key);

	// Destruir objeto
	bool removeObject(GraphicalObject* gO);
	bool removeObject(std::string key);

	// Marcar objeto para destrucción segura (control de cuándo)
	void sunsetObject(GraphicalObject* gO);
	bool sunsetObject(std::string key);

	// Destruir todos los objetos (asegurarse al final)
	void removeObjects();

	// Destruir aquellos objetos que fueron marcados previamente
	bool refreshObjects();

	// Obtener número de objetos
	int getNumObjects();
	// Obtener número de objetos marcados para borrar
	int getNumObjectsToRemove();

	// ¿Visualizar alambres de mallas?
	void objectShowMode(int val);

	// Cambiar fondo
	void setBgColor(float r, float g, float b);

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

	// Crear malla por código: plano
	void createPlaneMesh(Ogre::String name = "mPlane1080x800");

	// Punteros
	Ogre::SceneManager* mSM = nullptr;
	Ogre::Camera* cam = nullptr;
	/* cámara y puerto de vista */
	Ogre::Viewport* vp = nullptr;
	Ogre::SceneNode* mCamNode = nullptr;

private:
	// Colores de tripulantes
	#define NUM_CREWMATES 16
	const Ogre::String crew_colors[NUM_CREWMATES]
	{
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
