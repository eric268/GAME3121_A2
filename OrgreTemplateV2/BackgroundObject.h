#pragma once
#include "GameObject.h"
#include "DoodlePlayer.h"

class BackgroundObject : public GameObject
{
	DoodlePlayer* doodlePlayerRef;
	float backgroundZExtent;
	float distanceToPlayer;
	Vector3 m_vBackgroundStartingPosition;
	//float distanceFrom
public:
	BackgroundObject();
	BackgroundObject(Ogre::SceneNode* node, Ogre::SceneManager* scnMgr, DoodlePlayer* playerRef, int idNumber);
	~BackgroundObject();
	float GetBackgroundZExtent();
	Vector3 GetBackgroundStartingPosition();
	void SetBackgroundStartingPosition(Vector3 startingPos);

private:
	bool frameStarted(const Ogre::FrameEvent& evt);

};

