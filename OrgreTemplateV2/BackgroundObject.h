#pragma once
#include "GameObject.h"
#include "DoodlePlayer.h"

class BackgroundObject : public GameObject
{
	DoodlePlayer* doodlePlayerRef;
	float backgroundZExtent;
	float distanceToPlayer;
	//float distanceFrom
public:
	BackgroundObject();
	BackgroundObject(Ogre::SceneNode* node, Ogre::SceneManager* scnMgr, DoodlePlayer* playerRef, int idNumber);
	~BackgroundObject();
	float GetBackgroundZExtent();

private:
	bool frameStarted(const Ogre::FrameEvent& evt);

};

