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

SceneNode* Collider::GetSceneNode()
{
	return m_attachedSceneNode;
}




CubeCollider::CubeCollider(SceneNode* attachedSceneNode)
{
	SetColliderType(CUBE);
	SetAttachedSceneNode(attachedSceneNode);
	SetAllEdges(10.0f);
	SetIsTrigger(false);
	SetLocalPosition(Vector3(0, 0, 0));
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
