#include "Platform.h"
#define DEBUG


Platform::Platform()
{
	SetSceneNode(nullptr);
	SetEntity(nullptr);

	m_physicsBody = new PhysicsBody(GetAttachedSceneNode());
	m_cubeCollider = new CubeCollider(GetAttachedSceneNode());
	m_physicsBody->SetVelocity(Ogre::Vector3(0, 0, 0));
	m_physicsBody->SetSpeed(130.0f);
	m_fBounds = 0;
	m_pointEarned = false;
	m_iLivesRemaining = 5;
	m_iScore = 0;
	SetScale(Ogre::Vector3(0.5f, 0.1f, 0.1f));
	m_physicsBody->SetWeight(1.0f);
	m_lifeLost = false;
	m_playerRef = nullptr;

}


Platform::Platform(Ogre::SceneNode* player, Ogre::SceneManager* scnMgr, DoodlePlayer* playerRef)
{

	SetEntity(scnMgr->createEntity("Player1Entity", "WoodPallet.mesh"));

	//GetEntity()->setMaterial(Ogre::MaterialManager::getSingleton().getByName("penguin")); 
	GetEntity()->setCastShadows(false);
	SetSceneNode(player);
	GetAttachedSceneNode()->attachObject(GetEntity());

	scnMgr->getRootSceneNode()->addChild(GetAttachedSceneNode());
	SetScale(Ogre::Vector3(10.0f, 10.0f, 10.0f));

	GetAttachedSceneNode()->setScale(GetScale());
	GetAttachedSceneNode()->setPosition(Ogre::Vector3(-100, 0, 130));

	GetAttachedSceneNode()->pitch(Degree(-90));

	m_physicsBody = new PhysicsBody(GetAttachedSceneNode());
	m_cubeCollider = new CubeCollider(GetAttachedSceneNode());

	m_cubeCollider->SetAllExtent(Vector3(35.0f,25.0f,5.0f));

	m_physicsBody->SetVelocity(Ogre::Vector3(0, 0, 0));
	m_physicsBody->SetSpeed(130.0f);
	m_fBounds = 195;
	m_pointEarned = false;
	m_iLivesRemaining = 5;
	m_iScore = 0;
	m_physicsBody->SetWeight(1.0f);
	m_lifeLost = false;

	m_playerRef = playerRef;

	GetEntity()->setPolygonModeOverrideable(false);

#ifdef DEBUG

	m_cubeCollider->CreateBoundingBox(scnMgr);
#endif // DEBUG


}

Platform::~Platform()
{

}

int Platform::GetScore()
{
	return m_iScore;
}

int Platform::GetLivesRemaining()
{
	return m_iLivesRemaining;
}

void Platform::IncrementScore()
{
	m_iScore++;
}

void Platform::SetScore(int score)
{
	m_iScore = score;
}

void Platform::DecrementLivesRemaining()
{
	m_iLivesRemaining--;
}

void Platform::SetLivesRemaining(int livesRemaining)
{
	m_iLivesRemaining = livesRemaining;
}

bool Platform::GetPointEarned()
{
	return m_pointEarned;
}

void Platform::SetPointEarned(bool pEarned)
{
	m_pointEarned = pEarned;
}
void Platform::SetLifeLabel(bool lifeLost)
{
	m_lifeLost = lifeLost;
}
bool Platform::GetLifeLost()
{
	return m_lifeLost;
}
void Platform::BoundsChecking()
{
	if (GetAttachedSceneNode()->getPosition().x <= -m_fBounds)
	{
		Ogre::Vector3 temp = GetAttachedSceneNode()->getPosition();
		GetAttachedSceneNode()->setPosition(Ogre::Vector3(-m_fBounds, temp.y, temp.z));
	}
	else if (GetAttachedSceneNode()->getPosition().x >= m_fBounds)
	{
		Ogre::Vector3 temp = GetAttachedSceneNode()->getPosition();
		GetAttachedSceneNode()->setPosition(Ogre::Vector3(m_fBounds, temp.y, temp.z));
	}
}
bool Platform::frameStarted(const Ogre::FrameEvent& evt)
{
	//GetSceneNode()->translate(GetVelocity() * evt.timeSinceLastFrame);

	//BoundsChecking();

	if (CollisionManager::AABBCollision(m_cubeCollider, m_playerRef->GetCubeCollider()))
	{
		CollisionWithPlayer();
	}

	return true;
}

void Platform::CollisionWithPlayer()
{
	float z1 = m_playerRef->GetCubeCollider()->GetWorldPosition().z + m_playerRef->GetCubeCollider()->GetZExtent();
	float z2 = m_cubeCollider->GetWorldPosition().z - m_playerRef->GetCubeCollider()->GetZExtent();
	float overlap = z2 - z1;
	m_playerRef->GetAttachedSceneNode()->translate(0,0, -overlap);
	IncrementScore();
	SetPointEarned(true);
	m_playerRef->PlayerHitPlatform();
}

PhysicsBody* Platform::GetPhysicsBody()
{
	return m_physicsBody;
}

Collider* Platform::GetCubeCollider()
{
	return m_cubeCollider;
}
