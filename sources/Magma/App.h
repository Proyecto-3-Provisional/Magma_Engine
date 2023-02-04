#pragma once

#include "AppContext.h"

class App : public AppContext
{
public:
  explicit App() : AppContext("MagmaTest") { };  // new -> setup()  
  virtual ~App() { };    // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();
      
  Ogre::SceneManager* mSM = nullptr;   
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* mSinbadNode = nullptr;
};
