#pragma once
#include "Ogre.h"

using namespace Ogre;

enum ColliderType
{
	NONE = -1,
	CUBE,
	SPHERE,
	CAPSULE,
	NUM_COLLIDER_TYPES,
};

class Collider
{
public:
	Collider();
	Collider(SceneNode* attachedSceneNode);
	~Collider();

	void SetColliderType(ColliderType colliderType);
	ColliderType GetColliderType();

	void SetIsTrigger(bool isTrigger);
	bool GetIsTrigger();

	void SetLocalPosition(Ogre::Vector3 localPosition);
	Ogre::Vector3 GetLocalPosition();

	void SetAttachedSceneNode(SceneNode* attachedSceneNode);
	SceneNode* GetAttachedSceneNode();

	Vector3 GetWorldPosition();

private:
	ColliderType m_colliderType;
	bool m_isTrigger;
	Ogre::Vector3 m_localPosition;
	Ogre::SceneNode* m_attachedSceneNode;
};

class CubeCollider : public Collider
{
public:
	CubeCollider(SceneNode* attachedSceneNode);
	~CubeCollider();

	float GetXExtent();
	float GetYExtent();
	float GetZExtent();

	void SetXExtent(float length);
	void SetYExtent(float length);
	void SetZExtent(float length);

	void SetAllExtent(float length);
	void SetAllExtent(Vector3 vec);

	Vector3 GetExtents();

	void CreateBoundingBox(Ogre::SceneManager* scnMgr);
	void TranslateBoundingBox(Vector3 pos);

	float GetMinX();
	float GetMaxX();
	float GetMinY();
	float GetMaxY();
	float GetMinZ();
	float GetMaxZ();


private:
	SceneNode* m_boundingBoxNode;
	bool boundingBoxNodeCreated;

	float xExtent;
	float yExtent;
	float zExtent;

	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;
};

class SphereCollider: public Collider
{
public:
	SphereCollider(SceneNode* attachedSceneNode);
	~SphereCollider();

	float GetRadius();
	void SetRadius(float radius);
	void CreateSphericalBoundingBox(SceneManager* scnMgr);
	void TranslateSphericalBoundingBox(Vector3 pos);

private:
	float m_radius;
	SceneNode* sphericalBoundingBoxNode;
	bool boundingBoxNodeCreated;
};

class CapsuleCollider : public Collider
{
public:
	CapsuleCollider(SceneNode* attachedSceneNode);
	~CapsuleCollider();

	float GetRadius();
	float GetHeight();

	void SetRadius(float radius);
	void SetHeight(float height);

private:
	float m_radius;
	float m_height;
};
