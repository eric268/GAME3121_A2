#include "DoodlePlayer.h"
#include <string>
#include <iostream>
//#define DEBUG

DoodlePlayer::DoodlePlayer()
{
	SetSceneNode(nullptr);
	SetEntity(nullptr);
	m_physicsBody->SetVelocity(Ogre::Vector3(0, 0, 0));
	m_physicsBody->SetSpeed(25.0f);
	m_bIsColliding = false;
	SetScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
	m_physicsBody->SetWeight(1.0f);
	m_radius = 100.0f * GetScale().x;
	distanceFromCameraToPlayerZAxis = 0;
	isFacingLeft = false;
	camera = nullptr;
	cameraNode = nullptr;
	m_cubeCollider = nullptr;
	m_iLivesRemaining = 3;
}

DoodlePlayer::DoodlePlayer(Ogre::SceneNode* node, Ogre::SceneManager* scnMgr)
{
	SetEntity(scnMgr->createEntity("penguin.mesh"));
	GetEntity()->setCastShadows(false);

	SetSceneNode(node);
	GetAttachedSceneNode()->attachObject(GetEntity());
	scnMgr->getRootSceneNode()->addChild(GetAttachedSceneNode());
	SetScale(Ogre::Vector3(1.0f, 1.0f, 1.0f));
	GetAttachedSceneNode()->setScale(GetScale());
	GetAttachedSceneNode()->setPosition(Ogre::Vector3(0, 0, 0));
	GetAttachedSceneNode()->roll(Degree(90));
	GetAttachedSceneNode()->pitch(Degree(-90));
	distanceFromCameraToPlayerZAxis = 0;
	isFacingLeft = true;
	m_iLivesRemaining = 3;

	//Physics body initalization
	m_physicsBody = new PhysicsBody(GetAttachedSceneNode());
	m_physicsBody->SetSpeed(100.0f);
	m_physicsBody->SetVelocity(Ogre::Vector3(0, 0, 0));
	m_physicsBody->SetWeight(1.0f);
	m_physicsBody->SetGravityScale(10.0f);
	m_physicsBody->SetIsAffectedByGravity(true);

	//Creates box collider for player
	m_bIsColliding = false;
	m_cubeCollider = new CubeCollider(GetAttachedSceneNode());
	m_cubeCollider->SetAllExtent(Vector3(25.0f, 25.0f, 3.0f));
	m_cubeCollider->SetLocalPosition(Vector3(0, 0, 20));

	//Creates player follow camera
	CreatePlayerCamera(scnMgr);

#ifdef DEBUG
	m_cubeCollider->CreateBoundingBox(scnMgr);
	camera->setPolygonMode(Ogre::PolygonMode::PM_WIREFRAME);
#endif // DEBUG
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
	
	if (GetAttachedSceneNode()->getPosition().x <= -m_xBounds)
	{
		GetAttachedSceneNode()->setPosition(Vector3(m_xBounds - 10, GetAttachedSceneNode()->getPosition().y, GetAttachedSceneNode()->getPosition().z));
		/*Ogre::Vector3 temp = GetSceneNode()->getPosition();
		float overlap = GetSceneNode()->getPosition().x - GetRadius() + m_xBounds;
		GetSceneNode()->setPosition(Ogre::Vector3(GetSceneNode()->getPosition().x - overlap, temp.y, temp.z));
		SetVelocity(Ogre::Vector3(GetVelocity().x * -1, GetVelocity().y, GetVelocity().z));*/
	}
	else if (GetAttachedSceneNode()->getPosition().x >= m_xBounds)
	{
		GetAttachedSceneNode()->setPosition(Vector3(-m_xBounds + 10, GetAttachedSceneNode()->getPosition().y, GetAttachedSceneNode()->getPosition().z));
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
	m_physicsBody->Update(evt.timeSinceLastFrame);

	CheckBounds();
	if (m_iLivesRemaining <= 0)
	{
		GetAttachedSceneNode()->setPosition(Ogre::Vector3(0, 0, 0));
		m_physicsBody->SetVelocity(Ogre::Vector3(0, 0, 0));
	}

	distanceFromCameraToPlayerZAxis = cameraNode->getPosition().z - GetAttachedSceneNode()->getPosition().z;
	UpdateCameraPosition(evt);

#ifdef DEBUG
	m_cubeCollider->TranslateBoundingBox(m_physicsBody->GetVelocity() * evt.timeSinceLastFrame);
#endif // DEBUG
	
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
		cameraNode->translate(0,0,GetPhysicsBody()->GetVelocity().z * evt.timeSinceLastFrame);
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
		GetAttachedSceneNode()->yaw(Degree(-180));
	}
	else if (input == 'd' && isFacingLeft)
	{
		isFacingLeft = false;
		GetAttachedSceneNode()->yaw(Degree(180));
	}
}

PhysicsBody* DoodlePlayer::GetPhysicsBody()
{
	return m_physicsBody;
}

CubeCollider* DoodlePlayer::GetCubeCollider()
{
	return m_cubeCollider;
}

int DoodlePlayer::GetLivesRemaining()
{
	return m_iLivesRemaining;
}

void DoodlePlayer::SetLivesRemaining(int livesRemaining)
{
	m_iLivesRemaining = livesRemaining;
}

void DoodlePlayer::PlayerHitPlatform()
{
	m_physicsBody->SetVelocity(Vector3(m_physicsBody->GetVelocity().x, 0, 0));
	m_physicsBody->AddImpulse(Vector3(0, 0, 1), -200.0f);
}
