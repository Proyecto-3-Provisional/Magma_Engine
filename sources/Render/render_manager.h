#pragma once

#include "render_manager_context.h"

class render_manager : public render_manager_context
{
#define NUM_CREWMATES 16 // Colores de tripulantes
public:
	explicit render_manager(); // new -> setup()
	virtual ~render_manager(); // delete -> shutdown()

	// Ejemplo de movimiento
	void rotate(float deltaTime);

protected:
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
