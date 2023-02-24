#pragma once

#include "AppContext.h"

#define NUM_CREWMATES 16

class App : public AppContext
{
public:
  explicit App() : AppContext("MagmaTest") { };  // new -> setup()
  virtual ~App() { };    // delete -> shutdown()

  void rotate(float deltaTime);
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();
      
  Ogre::SceneManager* mSM = nullptr;   
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* mCubeNode = nullptr;
  Ogre::SceneNode* mPlaneNode = nullptr;

  Ogre::SceneNode* mCrewNode = nullptr;
  Ogre::Entity* mCrew[NUM_CREWMATES];

private:
    float rotationVelocity = 0.05;
};
