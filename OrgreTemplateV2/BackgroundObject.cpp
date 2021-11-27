#include "BackgroundObject.h"

BackgroundObject::BackgroundObject()
{
	SetScale(Ogre::Vector3(0, 0, 0));
	
	SetSceneNode(nullptr);
	GetSceneNode()->setScale(GetScale());
	GetSceneNode()->setPosition(0, 10, 0);
	GetSceneNode()->setPosition(0, 0, 0);
	backgroundZExtent = 0;
	distanceToPlayer = 0;
	doodlePlayerRef = nullptr;
}

BackgroundObject::BackgroundObject(Ogre::SceneNode* node, Ogre::SceneManager* scnMgr, DoodlePlayer* playerRef, int idNumber)
{
	SetEntity(scnMgr->createEntity(("BackgroundEntity" +std::to_string(idNumber)), "cube.mesh"));
	GetEntity()->setMaterial(Ogre::MaterialManager::getSingleton().getByName("DoodleBackground"));
	GetEntity()->setCastShadows(false);
	SetScale(Ogre::Vector3(4.5f, 0.01f, 4.5f));

	SetSceneNode(node);
	GetSceneNode()->attachObject(GetEntity());
	scnMgr->getRootSceneNode()->addChild(GetSceneNode());
	GetSceneNode()->setScale(GetScale());
	GetSceneNode()->setPosition(0, -10, 0);

	doodlePlayerRef = playerRef;
	distanceToPlayer = GetSceneNode()->getPosition().z - playerRef->GetSceneNode()->getPosition().z;
	backgroundZExtent = GetSceneNode()->getPosition().z + (50.0f * GetScale().z);
}

BackgroundObject::~BackgroundObject()
{
}

float BackgroundObject::GetBackgroundZExtent()
{
	return backgroundZExtent;
}

bool BackgroundObject::frameStarted(const Ogre::FrameEvent& evt)
{
	float playerZPosition = doodlePlayerRef->GetSceneNode()->getPosition().z;
	distanceToPlayer = GetSceneNode()->getPosition().z - playerZPosition;

	if (distanceToPlayer > backgroundZExtent)
	{
		GetSceneNode()->setPosition(0, -10, playerZPosition - backgroundZExtent);
	}

	return true;
}
