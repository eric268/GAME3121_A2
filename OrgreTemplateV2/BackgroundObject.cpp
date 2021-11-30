#include "BackgroundObject.h"

BackgroundObject::BackgroundObject()
{
	SetScale(Ogre::Vector3(0, 0, 0));
	
	SetSceneNode(nullptr);
	GetAttachedSceneNode()->setScale(GetScale());
	GetAttachedSceneNode()->setPosition(0, 10, 0);
	GetAttachedSceneNode()->setPosition(0, 0, 0);
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
	GetAttachedSceneNode()->attachObject(GetEntity());
	scnMgr->getRootSceneNode()->addChild(GetAttachedSceneNode());
	GetAttachedSceneNode()->setScale(GetScale());
	GetAttachedSceneNode()->setPosition(0, -10, 0);
	m_vBackgroundStartingPosition = Vector3(0, -10, 0);

	doodlePlayerRef = playerRef;
	distanceToPlayer = GetAttachedSceneNode()->getPosition().z - playerRef->GetAttachedSceneNode()->getPosition().z;
	backgroundZExtent = GetAttachedSceneNode()->getPosition().z + (50.0f * GetScale().z);
	GetEntity()->setPolygonModeOverrideable(false);
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
	float playerZPosition = doodlePlayerRef->GetAttachedSceneNode()->getPosition().z;
	distanceToPlayer = GetAttachedSceneNode()->getPosition().z - playerZPosition;

	if (distanceToPlayer > backgroundZExtent)
	{
		GetAttachedSceneNode()->setPosition(0, -10, playerZPosition - backgroundZExtent);
	}

	if (doodlePlayerRef->GetGameOver())
		GetAttachedSceneNode()->setVisible(false);
	else
		GetAttachedSceneNode()->setVisible(true);

	return true;
}

Vector3 BackgroundObject::GetBackgroundStartingPosition()
{
	return m_vBackgroundStartingPosition;
}

void BackgroundObject::SetBackgroundStartingPosition(Vector3 startingPos)
{
	m_vBackgroundStartingPosition = startingPos;
}
