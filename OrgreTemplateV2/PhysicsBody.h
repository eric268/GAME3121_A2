#pragma once
#include "Ogre.h"
using namespace Ogre;

class PhysicsBody
{
private:
	bool m_isAffectedByGravity;
	float m_gravityScale;
	Vector3 m_velocity;
	SceneNode* m_attachedSceneNode;

public:
	PhysicsBody();
	PhysicsBody(SceneNode* attachedBodyNode);
	~PhysicsBody();

	void Update(float deltaTime);
	void AddImpulse(Vector3 direction, float force);

	bool GetIsAffectedByGravity();
	void SetIsAffectedByGravity(bool m_isAffectedByGravity);

	float GetGravityScale();
	void SetGravityScale(float gravityScale);

	Vector3 GetVelocity();
	void SetVelocity(Vector3 velocity);
};


