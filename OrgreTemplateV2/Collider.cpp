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
	SetAllExtent(10.0f);
	SetIsTrigger(false);
	SetLocalPosition(Vector3(0, 0, 0));
	boundingBoxNodeCreated = false;
}

CubeCollider::~CubeCollider()
{
}

float CubeCollider::GetXExtent()
{
	return xExtent;
}

float CubeCollider::GetYExtent()
{
	return yExtent;
}

float CubeCollider::GetZExtent()
{
	return zExtent;
}

void CubeCollider::SetXExtent(float length)
{
	xExtent = length;
}

void CubeCollider::SetYExtent(float length)
{
	yExtent = length;
}

void CubeCollider::SetZExtent(float length)
{
	zExtent = length;
}

void CubeCollider::SetAllExtent(float length)
{
	SetXExtent(length);
	SetYExtent(length);
	SetZExtent(length);
}

void CubeCollider::SetAllExtent(Vector3 vec)
{
	SetXExtent(vec.x);
	SetYExtent(vec.y);
	SetZExtent(vec.z);
}

Vector3 CubeCollider::GetExtents()
{
	return Vector3(xExtent, yExtent, zExtent);
}

void CubeCollider::CreateBoundingBox(Ogre::SceneManager* scnMgr, int idNumber)
{
	Entity* entity = scnMgr->createEntity("cube.mesh");
	std::string name = "BoundingBox " + std::to_string(idNumber);
	m_boundingBoxNode = scnMgr->createSceneNode(name);
	m_boundingBoxNode->attachObject(entity);
	m_boundingBoxNode->setScale(xExtent/50.0f, yExtent / 50.0f, zExtent / 50.0f);

	m_boundingBoxNode->setPosition(Vector3(GetAttachedSceneNode()->getPosition().x + GetLocalPosition().x, GetAttachedSceneNode()->getPosition().y + GetLocalPosition().y,
		GetAttachedSceneNode()->getPosition().z + GetLocalPosition().z));
	
	scnMgr->getRootSceneNode()->addChild(m_boundingBoxNode);
	boundingBoxNodeCreated = true;
	entity->setMaterial(Ogre::MaterialManager::getSingleton().getByName("Platform"));
}

void CubeCollider::TranslateBoundingBox(Vector3 pos)
{
	if (boundingBoxNodeCreated)
	{
		m_boundingBoxNode->translate(pos);
	}
}

float CubeCollider::GetMinX()
{
	minX = GetWorldPosition().x - GetXExtent();
	return minX;
}

float CubeCollider::GetMaxX()
{
	maxX = GetWorldPosition().x + GetXExtent();
	return maxX;
}

float CubeCollider::GetMinY()
{
	minY = GetWorldPosition().y - GetYExtent();
	return minY;
}

float CubeCollider::GetMaxY()
{
	maxY = GetWorldPosition().y + GetYExtent();
	return maxY;
}

float CubeCollider::GetMinZ()
{
	minZ = GetWorldPosition().z - GetZExtent();
	return minZ;
}

float CubeCollider::GetMaxZ()
{
	maxZ = GetWorldPosition().z + GetZExtent();
	return maxZ;
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

void SphereCollider::CreateSphericalBoundingBox(SceneManager* scnMgr, int idNumber)
{
	Entity* entity = scnMgr->createEntity("sphere.mesh");
	sphericalBoundingBoxNode = scnMgr->createSceneNode("Sphere bounding box: " + idNumber);
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

