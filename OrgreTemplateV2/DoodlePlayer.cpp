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
	distanceFromCameraToPlayerZAxis = 0;
	isFacingLeft = false;
	camera = nullptr;
	cameraNode = nullptr;
	m_cubeCollider = nullptr;
	m_iLivesRemaining = 3;
	m_bGameOver = false;
	m_bGameWon = false;
	playerDiedZValue = -150.0f;
}

DoodlePlayer::DoodlePlayer(Ogre::SceneNode* node, Ogre::SceneManager* scnMgr, Platform** platformRef,Log* gameLogRef, int numPlatforms)
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
	m_bPointEarned = false;
	m_bLifeLost = false;
	m_iLivesRemaining = 3;

	m_gameLogRef = gameLogRef;
	m_fTotalGameTime = 0.0f;

	//Physics body initalization
	m_physicsBody = new PhysicsBody(GetAttachedSceneNode());
	m_physicsBody->SetSpeed(200.0f);
	m_physicsBody->SetVelocity(Ogre::Vector3(0, 0, 0));
	m_physicsBody->SetWeight(1.0f);
	m_physicsBody->SetGravityScale(20.0f);
	m_physicsBody->SetIsAffectedByGravity(true);

	//Creates box collider for player
	m_bIsColliding = false;
	m_cubeCollider = new CubeCollider(GetAttachedSceneNode());
	m_cubeCollider->SetAllExtent(Vector3(25.0f, 25.0f, 3.0f));
	m_cubeCollider->SetLocalPosition(Vector3(0, 0, 20));

	m_platformArrayRef = platformRef;
	m_iNumberOfPlatforms = numPlatforms;
	m_bGameOver = false;
	m_bGameWon = false;
	playerDiedZValue = -150.0f;
	//Creates player follow camera
	CreatePlayerCamera(scnMgr);

#ifdef DEBUG
	m_cubeCollider->CreateBoundingBox(scnMgr, 0);
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

void DoodlePlayer::CheckBounds()
{
	float m_xBounds = 220;
	float m_zBounds = 165;
	
	if (GetAttachedSceneNode()->getPosition().x <= -m_xBounds)
	{
		GetAttachedSceneNode()->setPosition(Vector3(m_xBounds - 10, GetAttachedSceneNode()->getPosition().y, GetAttachedSceneNode()->getPosition().z));
	}
	else if (GetAttachedSceneNode()->getPosition().x >= m_xBounds)
	{
		GetAttachedSceneNode()->setPosition(Vector3(-m_xBounds + 10, GetAttachedSceneNode()->getPosition().y, GetAttachedSceneNode()->getPosition().z));
	}
	else if (distanceFromCameraToPlayerZAxis <= playerDiedZValue)
	{
		//std::cout << distanceFromCameraToPlayerZAxis << std::endl;
		//
		//SetVelocity(Ogre::Vector3(0, 0, GetSpeed()));
		DecrementLivesRemaining();
		SetLifeLabel(true);
		if (m_iLivesRemaining <= 0 && !m_bGameOver)
		{
			m_bGameOver = true;
			m_physicsBody->SetVelocity(Ogre::Vector3(0, 0, 0));
			GetAttachedSceneNode()->setPosition(0, 0, cameraNode->getPosition().z);
			m_physicsBody->SetIsAffectedByGravity(false);
			m_bGameOver = true;
			m_bGameWon = false;
			m_physicsBody->SetIsAffectedByGravity(false);
			HidePlayerAndPlatforms();
		}
		else
		{
			m_physicsBody->SetVelocity(Ogre::Vector3(0, 0, 0));
			GetAttachedSceneNode()->setPosition(0,0,cameraNode->getPosition().z);
		}
	}
}

bool DoodlePlayer::frameStarted(const Ogre::FrameEvent& evt)
{
	if (!m_bGameOver)
	{
		m_fTotalGameTime += evt.timeSinceLastFrame;
		m_physicsBody->Update(evt.timeSinceLastFrame);

		CheckBounds();
		UpdateCameraPosition(evt);
		CheckForCollisionWithPlatform();
		if (m_iLivesRemaining <= 0)
		{
			GetAttachedSceneNode()->setPosition(Ogre::Vector3(0, 0, 0));
			m_physicsBody->SetVelocity(Ogre::Vector3(0, 0, 0));
		}
	}


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
	distanceFromCameraToPlayerZAxis = cameraNode->getPosition().z - GetAttachedSceneNode()->getPosition().z;
	if (distanceFromCameraToPlayerZAxis > 20)
	{
		cameraNode->translate(0,0,GetPhysicsBody()->GetVelocity().z * evt.timeSinceLastFrame);
	}
}

SceneNode* DoodlePlayer::GetCameraNode()
{
	return cameraNode;
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
	m_physicsBody->AddImpulse(Vector3(0, 0, 1), -250.0f);
}

void DoodlePlayer::SetGameOver(bool gameOver)
{
	m_bGameOver = gameOver;
}

void DoodlePlayer::SetGameWon(bool gameWon)
{
	m_bGameWon = gameWon;
}

bool DoodlePlayer::GetGameOver()
{
	return m_bGameOver;
}

bool DoodlePlayer::GetGameWon()
{
	return m_bGameWon;
}

void DoodlePlayer::HidePlayerAndPlatforms()
{
	GetAttachedSceneNode()->setVisible(false);
	for (int i = 0; i < m_iNumberOfPlatforms; i++)
		m_platformArrayRef[i]->GetAttachedSceneNode()->setVisible(false);
}

void DoodlePlayer::ResetPlayerAndPlatforms()
{
	GetAttachedSceneNode()->setVisible(true);
	for (int i = 0; i < m_iNumberOfPlatforms; i++)
	{
		m_platformArrayRef[i]->GetAttachedSceneNode()->setVisible(true);
		m_platformArrayRef[i]->SetPointEarned(false);
	}
}

int DoodlePlayer::GetScore()
{
	return m_iScore;
}

void DoodlePlayer::IncrementScore()
{
	m_iScore++;
}

void DoodlePlayer::SetScore(int score)
{
	m_iScore = score;
}

void DoodlePlayer::DecrementLivesRemaining()
{
	m_iLivesRemaining--;
}


bool DoodlePlayer::GetPointEarned()
{
	return m_bPointEarned;
}

void DoodlePlayer::SetPointEarned(bool pEarned)
{
	m_bPointEarned = pEarned;
}
void DoodlePlayer::SetLifeLabel(bool lifeLost)
{
	m_bLifeLost = lifeLost;
}
bool DoodlePlayer::GetLifeLost()
{
	return m_bLifeLost;
}
void DoodlePlayer::CollisionWithPlayer(Platform* platform)
{
	float z1 =m_cubeCollider->GetWorldPosition().z + m_cubeCollider->GetZExtent();
	float z2 = platform->GetCubeCollider()->GetWorldPosition().z - platform->GetCubeCollider()->GetZExtent();
	float overlap = z2 - z1;
	GetAttachedSceneNode()->translate(0, 0, -overlap);
	if (!platform->GetPointEarned())
	{
		platform->SetPointEarned(true);
		IncrementScore();
	}
	SetPointEarned(true);
	PlayerHitPlatform();
}

void DoodlePlayer::CheckForCollisionWithPlatform()
{
	if (m_physicsBody->GetVelocity().z >= 0 && !m_bGameOver)
	{
		for (int i = 0; i < m_iNumberOfPlatforms; i++)
		{
			if (CollisionManager::AABBCollision(m_cubeCollider, m_platformArrayRef[i]->GetCubeCollider()))
			{
				CollisionWithPlayer(m_platformArrayRef[i]);
				if (i == (m_iNumberOfPlatforms - 1))
				{
					m_bGameOver = true;
					m_bGameWon = true;
					m_physicsBody->SetIsAffectedByGravity(false);
					std::string message = "Total Game Time: " + std::to_string(m_fTotalGameTime);
					m_gameLogRef->logMessage(message, LML_NORMAL, false);
					m_fTotalGameTime = 0.0f;
					HidePlayerAndPlatforms();
				}
				break;
			}
		}
	}
}
