#include "DoodlePlayer.h"
#include <string>
#include <iostream>

DoodlePlayer::DoodlePlayer()
{
	SetSceneNode(nullptr);
	SetEntity(nullptr);
	SetVelocity(Ogre::Vector3(0, 0, 0));
	SetSpeed(25.0f);
	m_bIsColliding = false;
	SetScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
	SetWeight(1.0f);
	m_radius = 100.0f * GetScale().x;
	m_paddleRef = nullptr;
	distanceFromCameraToPlayerZAxis = 0;
	isFacingLeft = false;
}

DoodlePlayer::DoodlePlayer(Ogre::SceneNode* node, Ogre::SceneManager* scnMgr, PongPaddle* pRef)
{
	SetEntity(scnMgr->createEntity("penguin.mesh"));
	//GetEntity()->setMaterial(Ogre::MaterialManager::getSingleton().getByName("DoodlePlayer"));
	GetEntity()->setCastShadows(false);
	m_paddleRef = pRef;
	SetSceneNode(node);
	GetSceneNode()->attachObject(GetEntity());
	scnMgr->getRootSceneNode()->addChild(GetSceneNode());
	SetScale(Ogre::Vector3(1.0f, 1.0f, 1.0f));
	GetSceneNode()->setScale(GetScale());
	GetSceneNode()->setPosition(Ogre::Vector3(0, 0, 0));
	SetSpeed(25.0f);
	SetVelocity(Ogre::Vector3(0, 0, 0));
	//SetVelocity(Ogre::Vector3(0, 0, GetSpeed()));
	SetWeight(1.0f);
	m_radius = 100.0f * GetScale().x;
	m_bIsColliding = false;
	GetSceneNode()->roll(Degree(90));
	GetSceneNode()->pitch(Degree(-90));
	distanceFromCameraToPlayerZAxis = 0;
	CreatePlayerCamera(scnMgr);
	isFacingLeft = true;
}

DoodlePlayer::~DoodlePlayer()
{
}


bool DoodlePlayer::GetIsColliding()
{
	return m_bIsColliding;
}

void DoodlePlayer::SetIsColliding(bool colliding)
{
	m_bIsColliding = colliding;
}

void DoodlePlayer::VelocityAfterPaddleCollision()
{
	
	Ogre::Vector3 paddelMomentum = m_paddleRef->GetWeight() * m_paddleRef->GetVelocity();
	Ogre::Vector3 ballMomentum = GetWeight() * GetVelocity();
	Ogre::Vector3 totalMomentum = paddelMomentum + ballMomentum;

	float totalMass = m_paddleRef->GetWeight() + GetWeight();

	Ogre::Vector3 newVelocity = totalMomentum / 1;

	SetVelocity(Ogre::Vector3(newVelocity.x, 0, newVelocity.z * -1));
	

}

void DoodlePlayer::CollisionWithPaddle()
{
	float overlap = (m_paddleRef->GetSceneNode()->getPosition().z - 50.0f * m_paddleRef->GetScale().z) - GetSceneNode()->getPosition().z - GetRadius();
	GetSceneNode()->setPosition(GetSceneNode()->getPosition().x, GetSceneNode()->getPosition().y, GetSceneNode()->getPosition().z + overlap);
	VelocityAfterPaddleCollision();
	m_paddleRef->IncrementScore();
	m_paddleRef->SetPointEarned(true);
}

float DoodlePlayer::GetRadius()
{
	return m_radius;
}

void DoodlePlayer::SetRadius(float radius)
{
	m_radius = radius;
}

void DoodlePlayer::CheckBounds()
{
	float m_xBounds = 220;
	float m_zBounds = 165;
	
	if (GetSceneNode()->getPosition().x <= -m_xBounds)
	{
		GetSceneNode()->setPosition(Vector3(m_xBounds - 10, GetSceneNode()->getPosition().y, GetSceneNode()->getPosition().z));
		/*Ogre::Vector3 temp = GetSceneNode()->getPosition();
		float overlap = GetSceneNode()->getPosition().x - GetRadius() + m_xBounds;
		GetSceneNode()->setPosition(Ogre::Vector3(GetSceneNode()->getPosition().x - overlap, temp.y, temp.z));
		SetVelocity(Ogre::Vector3(GetVelocity().x * -1, GetVelocity().y, GetVelocity().z));*/
	}
	else if (GetSceneNode()->getPosition().x >= m_xBounds)
	{
		GetSceneNode()->setPosition(Vector3(-m_xBounds + 10, GetSceneNode()->getPosition().y, GetSceneNode()->getPosition().z));
		//Ogre::Vector3 temp = GetSceneNode()->getPosition();
		//float overlap = m_xBounds - GetSceneNode()->getPosition().x - GetRadius();
		//GetSceneNode()->setPosition(Ogre::Vector3(GetSceneNode()->getPosition().x + overlap, temp.y, temp.z));
		//SetVelocity(Ogre::Vector3(GetVelocity().x * -1, GetVelocity().y, GetVelocity().z));
	}
	else if (distanceFromCameraToPlayerZAxis <= playerDiedZValue)
	{
		std::cout << distanceFromCameraToPlayerZAxis << std::endl;
		//GetSceneNode()->setPosition(Ogre::Vector3(0, 0, 0));
		//SetVelocity(Ogre::Vector3(0, 0, GetSpeed()));
		//m_paddleRef->DecrementLivesRemaining();
		//m_paddleRef->SetLifeLabel(true);
	}
}

bool DoodlePlayer::frameStarted(const Ogre::FrameEvent& evt)
{
	GetSceneNode()->translate(GetVelocity() * evt.timeSinceLastFrame);

	CheckBounds();
	if (m_paddleRef->GetLivesRemaining() <= 0)
	{
		GetSceneNode()->setPosition(Ogre::Vector3(0, 0, 0));
		SetVelocity(Ogre::Vector3(0, 0, 0));
	}

	if (CollisionManager::AABBSphere(m_paddleRef, this))
	{
		//CollisionWithPaddle();
	}
	distanceFromCameraToPlayerZAxis = cameraNode->getPosition().z - GetSceneNode()->getPosition().z;


	UpdateCameraPosition(evt);
	
	return true;
}

Camera* DoodlePlayer::GetPlayerCamera()
{
	return camera;
}

void DoodlePlayer::CreatePlayerCamera(Ogre::SceneManager* scnMgr)
{
	cameraNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	// create the camera
	camera = scnMgr->createCamera("myCam");
	camera->setNearClipDistance(5); // specific to this sample
	camera->setAutoAspectRatio(true);
	cameraNode->attachObject(camera);
	cameraNode->setPosition(0, 400, 0);
	cameraNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);
}

void DoodlePlayer::UpdateCameraPosition(const Ogre::FrameEvent& evt)
{
	if (distanceFromCameraToPlayerZAxis > 20)
	{
		cameraNode->translate(0,0, GetVelocity().z * evt.timeSinceLastFrame);
	}

}

void DoodlePlayer::SetIsFacingLeft(bool dir)
{
	isFacingLeft = dir;
}

bool DoodlePlayer::GetIsFacingLeft()
{
	return isFacingLeft;
}

void DoodlePlayer::UpdatePlayerDirection(char input)
{
	if (input == 'a' && !isFacingLeft)
	{
		isFacingLeft = true;
		GetSceneNode()->yaw(Degree(-180));
	}
	else if (input == 'd' && isFacingLeft)
	{
		isFacingLeft = false;
		GetSceneNode()->yaw(Degree(180));
	}
}
