#include "PongPaddle.h"

PongPaddle::PongPaddle()
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

}


PongPaddle::PongPaddle(Ogre::SceneNode* player, Ogre::SceneManager* scnMgr)
{

	SetEntity(scnMgr->createEntity("Player1Entity", "cube.mesh"));

	//GetEntity()->setMaterial(Ogre::MaterialManager::getSingleton().getByName("DoodlePlatform")); 
	GetEntity()->setCastShadows(false);
	SetSceneNode(player);
	GetAttachedSceneNode()->attachObject(GetEntity());

	scnMgr->getRootSceneNode()->addChild(GetAttachedSceneNode());
	SetScale(Ogre::Vector3(0.5f, 0.2f, 0.2f));

	GetAttachedSceneNode()->setScale(GetScale());
	GetAttachedSceneNode()->setPosition(Ogre::Vector3(-100, 0, 130));

	m_physicsBody = new PhysicsBody(GetAttachedSceneNode());
	m_cubeCollider = new CubeCollider(GetAttachedSceneNode());
	m_physicsBody->SetVelocity(Ogre::Vector3(0, 0, 0));
	m_physicsBody->SetSpeed(130.0f);
	m_fBounds = 195;
	m_pointEarned = false;
	m_iLivesRemaining = 5;
	m_iScore = 0;
	m_physicsBody->SetWeight(1.0f);
	m_lifeLost = false;
}

PongPaddle::~PongPaddle()
{

}

int PongPaddle::GetScore()
{
	return m_iScore;
}

int PongPaddle::GetLivesRemaining()
{
	return m_iLivesRemaining;
}

void PongPaddle::IncrementScore()
{
	m_iScore++;
}

void PongPaddle::SetScore(int score)
{
	m_iScore = score;
}

void PongPaddle::DecrementLivesRemaining()
{
	m_iLivesRemaining--;
}

void PongPaddle::SetLivesRemaining(int livesRemaining)
{
	m_iLivesRemaining = livesRemaining;
}

bool PongPaddle::GetPointEarned()
{
	return m_pointEarned;
}

void PongPaddle::SetPointEarned(bool pEarned)
{
	m_pointEarned = pEarned;
}
void PongPaddle::SetLifeLabel(bool lifeLost)
{
	m_lifeLost = lifeLost;
}
bool PongPaddle::GetLifeLost()
{
	return m_lifeLost;
}
void PongPaddle::BoundsChecking()
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
bool PongPaddle::frameStarted(const Ogre::FrameEvent& evt)
{
	//GetSceneNode()->translate(GetVelocity() * evt.timeSinceLastFrame);

	//BoundsChecking();

	return true;
}

PhysicsBody* PongPaddle::GetPhysicsBody()
{
	return m_physicsBody;
}

Collider* PongPaddle::GetCubeCollider()
{
	return m_cubeCollider;
}
