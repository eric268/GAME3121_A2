#include "Collider.h"

Collider::Collider()
{
	m_colliderType = NONE;
	m_isTrigger = false;
	m_localPosition = Vector3(0, 0, 0);
	m_attachedSceneNode = nullptr;
}

Collider::Collider(SceneNode* attachedSceneNode)
{
	m_attachedSceneNode = attachedSceneNode;
	m_colliderType = NONE;
	m_isTrigger = false;
	m_localPosition = Vector3(0, 0, 0);
}

Collider::~Collider()
{

}
void Collider::SetColliderType(ColliderType colliderType)
{
	m_colliderType = colliderType;
}

ColliderType Collider::GetColliderType()
{
	return m_colliderType;
}

void Collider::SetIsTrigger(bool isTrigger)
{
	m_isTrigger = isTrigger;
}

bool Collider::GetIsTrigger()
{
	return m_isTrigger;
}

void Collider::SetLocalPosition(Ogre::Vector3 localPosition)
{
	m_localPosition = localPosition;
}

Ogre::Vector3 Collider::GetLocalPosition()
{
	return m_localPosition;
}

void Collider::SetAttachedSceneNode(SceneNode* attachedSceneNode)
{
	m_attachedSceneNode = attachedSceneNode;
}

SceneNode* Collider::GetAttachedSceneNode()
{
	return m_attachedSceneNode;
}

Vector3 Collider::GetWorldPosition()
{
	float xPos = m_attachedSceneNode->getPosition().x + m_localPosition.x;
	float yPos = m_attachedSceneNode->getPosition().y + m_localPosition.y;
	float zPos = m_attachedSceneNode->getPosition().z + m_localPosition.z;
	return Vector3(xPos, yPos, zPos);
}





CubeCollider::CubeCollider(SceneNode* attachedSceneNode)
{
	SetColliderType(CUBE);
	SetAttachedSceneNode(attachedSceneNode);
	SetAllEdges(10.0f);
	SetIsTrigger(false);
	SetLocalPosition(Vector3(0, 0, 0));
	boundingBoxNodeCreated = false;
}

CubeCollider::~CubeCollider()
{
}

float CubeCollider::GetXLength()
{
	return xLength;
}

float CubeCollider::GetYLength()
{
	return yLength;
}

float CubeCollider::GetZLength()
{
	return zLength;
}

void CubeCollider::SetXLength(float length)
{
	xLength = length;
}

void CubeCollider::SetYLength(float length)
{
	yLength = length;
}

void CubeCollider::SetZLength(float length)
{
	zLength = length;
}

void CubeCollider::SetAllEdges(float length)
{
	SetXLength(length);
	SetYLength(length);
	SetZLength(length);
}

void CubeCollider::SetAllEdges(Vector3 vec)
{
	SetXLength(vec.x);
	SetYLength(vec.y);
	SetZLength(vec.z);
}

void CubeCollider::CreateBoundingBox(Ogre::SceneManager* scnMgr)
{
	Entity* entity = scnMgr->createEntity("cube.mesh");
	m_boundingBoxNode = scnMgr->createSceneNode("Player bounding box node");
	m_boundingBoxNode->attachObject(entity);
	m_boundingBoxNode->setScale(xLength/50.0f, yLength / 50.0f, zLength / 50.0f);

	m_boundingBoxNode->setPosition(Vector3(GetAttachedSceneNode()->getPosition().x + GetLocalPosition().x, GetAttachedSceneNode()->getPosition().y + GetLocalPosition().y,
		GetAttachedSceneNode()->getPosition().z + GetLocalPosition().z));
	
	scnMgr->getRootSceneNode()->addChild(m_boundingBoxNode);
	boundingBoxNodeCreated = true;
}

void CubeCollider::TranslateBoundingBox(Vector3 pos)
{
	if (boundingBoxNodeCreated)
	{
		m_boundingBoxNode->translate(pos);
	}
}


SphereCollider::SphereCollider(SceneNode* attachedSceneNode)
{
	SetColliderType(SPHERE);
	SetAttachedSceneNode(attachedSceneNode);
	m_radius = 10.0f;
	SetIsTrigger(false);
	SetLocalPosition(Vector3(0, 0, 0));
}

SphereCollider::~SphereCollider()
{
}

float SphereCollider::GetRadius()
{
	return m_radius;
}

void SphereCollider::SetRadius(float radius)
{
	m_radius = radius;
}

void SphereCollider::CreateSphericalBoundingBox(SceneManager* scnMgr)
{
	Entity* entity = scnMgr->createEntity("sphere.mesh");
	sphericalBoundingBoxNode = scnMgr->createSceneNode("Player spherical bounding box node");
	sphericalBoundingBoxNode->attachObject(entity);
	sphericalBoundingBoxNode->setScale(m_radius / 100.0f, m_radius / 100.0f, m_radius / 100.0f);

	sphericalBoundingBoxNode->setPosition(Vector3(GetAttachedSceneNode()->getPosition().x + GetLocalPosition().x, GetAttachedSceneNode()->getPosition().y + GetLocalPosition().y,
		GetAttachedSceneNode()->getPosition().z + GetLocalPosition().z));

	scnMgr->getRootSceneNode()->addChild(sphericalBoundingBoxNode);
	boundingBoxNodeCreated = true;
}

void SphereCollider::TranslateSphericalBoundingBox(Vector3 pos)
{
	if (boundingBoxNodeCreated)
	{
		sphericalBoundingBoxNode->translate(pos);
	}
}

CapsuleCollider::CapsuleCollider(SceneNode* attachedSceneNode)
{
	SetAttachedSceneNode(attachedSceneNode);
	SetColliderType(CAPSULE);
	m_radius = 5.0f;
	m_height = 10.0f;
	SetIsTrigger(false);
	SetLocalPosition(Vector3(0, 0, 0));
}

CapsuleCollider::~CapsuleCollider()
{
}

float CapsuleCollider::GetRadius()
{
	return m_radius;
}

float CapsuleCollider::GetHeight()
{
	return m_height;
}

void CapsuleCollider::SetRadius(float radius)
{
	m_radius = radius;
}

void CapsuleCollider::SetHeight(float height)
{
	m_height = height;
}

