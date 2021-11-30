#include "Platform.h"
//#define DEBUG


Platform::Platform()
{
	SetSceneNode(nullptr);
	SetEntity(nullptr);
	m_bPointEarned = false;
	m_cubeCollider = new CubeCollider(GetAttachedSceneNode());;
	SetScale(Ogre::Vector3(0.5f, 0.1f, 0.1f));
}


Platform::Platform(Ogre::SceneNode* player, Ogre::SceneManager* scnMgr, int platformIDNumber)
{
	std::string name = "PlatformEntity: " + std::to_string(platformIDNumber);
	SetEntity(scnMgr->createEntity(name, "WoodPallet.mesh"));
	GetEntity()->setCastShadows(false);
	SetSceneNode(player);
	GetAttachedSceneNode()->attachObject(GetEntity());
	scnMgr->getRootSceneNode()->addChild(GetAttachedSceneNode());
	SetScale(Ogre::Vector3(10.0f, 10.0f, 10.0f));
	GetAttachedSceneNode()->setScale(GetScale());
	GetAttachedSceneNode()->setPosition(Ogre::Vector3(-100, 0, 130));
	GetAttachedSceneNode()->pitch(Degree(-90));
	m_cubeCollider = new CubeCollider(GetAttachedSceneNode());
	m_cubeCollider->SetAllExtent(Vector3(35.0f,25.0f,5.0f));
	m_bPointEarned = false;

#ifdef DEBUG
	m_cubeCollider->CreateBoundingBox(scnMgr, m_iPlatformIDNumber);
#endif // DEBUG
}

Platform::~Platform()
{

}

bool Platform::frameStarted(const Ogre::FrameEvent& evt)
{
	return true;
}

CubeCollider* Platform::GetCubeCollider()
{
	return m_cubeCollider;
}

void Platform::SetPointEarned(bool pEarned)
{
	m_bPointEarned = pEarned;
}

bool Platform::GetPointEarned()
{
	return m_bPointEarned;
}
