#pragma once
#include "GameObject.h"

class BackgroundPlane : GameObject
{
	SceneNode* secondBackgroundNode;
	float backgroundHeight = 100;
public:
	BackgroundPlane(Ogre::SceneNode* node, Ogre::SceneManager* scnMgr, Camera* cameraNode);

private:
	bool frameStarted(const Ogre::FrameEvent& evt);

};

