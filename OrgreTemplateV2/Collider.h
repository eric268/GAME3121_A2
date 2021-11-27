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
	SceneNode* GetSceneNode();

private:
	ColliderType m_colliderType;
	bool m_isTrigger;
	Ogre::Vector3 m_localPosition;
	Ogre::SceneNode* m_attachedSceneNode;
};

class CubeCollider : public Collider
{
public:
	//CubeCollider();
	CubeCollider(SceneNode* attachedSceneNode);
	~CubeCollider();

	float GetXLength();
	float GetYLength();
	float GetZLength();

	void SetXLength(float length);
	void SetYLength(float length);
	void SetZLength(float length);

	void SetAllEdges(float length);

private:
	float xLength;
	float yLength;
	float zLength;
};

class SphereCollider: public Collider
{
public:
	SphereCollider(SceneNode* attachedSceneNode);
	~SphereCollider();

	float GetRadius();
	void SetRadius(float radius);

private:
	float m_radius;
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
