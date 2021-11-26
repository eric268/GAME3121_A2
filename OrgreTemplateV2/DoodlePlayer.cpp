#include "DoodlePlayer.h"
#include <string>
#include <iostream>

DoodlePlayer::DoodlePlayer()
{
	SetSceneNode(nullptr);
	SetEntity(nullptr);
	SetVelocity(Ogre::Vector3(0, 0, 0));
	SetSpeed(100.0f);
	m_bIsColliding = false;
	SetScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
	SetWeight(1.0f);
	m_radius = 100.0f * GetScale().x;
	m_paddleRef = nullptr;
	distanceFromCameraToPlayerZAxis = 0;
}

DoodlePlayer::DoodlePlayer(Ogre::SceneNode* node, Ogre::SceneManager* scnMgr, PongPaddle* pRef)
{
	SetEntity(scnMgr->createEntity("BallEntity", "cube.mesh"));
	GetEntity()->setMaterial(Ogre::MaterialManager::getSingleton().getByName("DoodlePlayer"));
	GetEntity()->setCastShadows(false);
	m_paddleRef = pRef;

	SetSceneNode(node);
	GetSceneNode()->attachObject(GetEntity());
	scnMgr->getRootSceneNode()->addChild(GetSceneNode());
	SetScale(Ogre::Vector3(0.5f, 0.01f, 1.0f));
	GetSceneNode()->setScale(GetScale());
	GetSceneNode()->setPosition(Ogre::Vector3(100, 0, -40));
	SetSpeed(25.0f);
	SetVelocity(Ogre::Vector3(0, 0, 0));
	//SetVelocity(Ogre::Vector3(0, 0, GetSpeed()));
	SetWeight(1.0f);
	m_radius = 100.0f * GetScale().x;
	m_bIsColliding = false;
	
	distanceFromCameraToPlayerZAxis = 0;
	CreatePlayerCamera(scnMgr);
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
	
	if (GetSceneNode()->getPosition().x - GetRadius() <= -m_xBounds)
	{
		Ogre::Vector3 temp = GetSceneNode()->getPosition();
		float overlap = GetSceneNode()->getPosition().x - GetRadius() + m_xBounds;
		GetSceneNode()->setPosition(Ogre::Vector3(GetSceneNode()->getPosition().x - overlap, temp.y, temp.z));
		SetVelocity(Ogre::Vector3(GetVelocity().x * -1, GetVelocity().y, GetVelocity().z));
	}
	else if (GetSceneNode()->getPosition().x + GetRadius() >= m_xBounds)
	{
		Ogre::Vector3 temp = GetSceneNode()->getPosition();
		float overlap = m_xBounds - GetSceneNode()->getPosition().x - GetRadius();
		GetSceneNode()->setPosition(Ogre::Vector3(GetSceneNode()->getPosition().x + overlap, temp.y, temp.z));
		SetVelocity(Ogre::Vector3(GetVelocity().x * -1, GetVelocity().y, GetVelocity().z));
	}
	else if (distanceFromCameraToPlayerZAxis <= 0.0f)
	{
		//GetSceneNode()->setPosition(Ogre::Vector3(0, 0, 0));
		//SetVelocity(Ogre::Vector3(0, 0, GetSpeed()));
		//m_paddleRef->DecrementLivesRemaining();
		//m_paddleRef->SetLifeLabel(true);
	}
}

bool DoodlePlayer::frameStarted(const Ogre::FrameEvent& evt)
{

	GetSceneNode()->translate(GetVelocity() * evt.timeSinceLastFrame);

	std::cout << "Main Node Postition: " + std::to_string(GetSceneNode()->getPosition().z) << std::endl;
	std::cout << "Camera Node Postition: " + std::to_string(cameraNode->getPosition().z) << std::endl;

	CheckBounds();
	if (m_paddleRef->GetLivesRemaining() <= 0)
	{
		GetSceneNode()->setPosition(Ogre::Vector3(0, 0, 0));
		SetVelocity(Ogre::Vector3(0, 0, 0));
	}

	if (CollisionManager::AABBSphere(m_paddleRef, this))
	{
		CollisionWithPaddle();
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
	if (distanceFromCameraToPlayerZAxis > 40)
	{
		
		cameraNode->translate(0,0, GetVelocity().z * evt.timeSinceLastFrame);
	}

}
