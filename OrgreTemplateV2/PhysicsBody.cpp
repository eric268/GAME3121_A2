#include "PhysicsBody.h"

PhysicsBody::PhysicsBody()
{
	m_gravityScale = 0;
	m_isAffectedByGravity = false;
	m_velocity = Vector3(0, 0, 0);
	m_attachedSceneNode = nullptr;
	m_fSpeed = 50.0f;
}

PhysicsBody::PhysicsBody(SceneNode* attachedBodyNode)
{
	m_isAffectedByGravity = true;
	m_gravityScale = 1;
	m_velocity = Vector3(0, 0, 0);
	m_attachedSceneNode = attachedBodyNode;
	m_fSpeed = 50.0f;
}

PhysicsBody::~PhysicsBody()
{
}

void PhysicsBody::Update(float deltaTime)
{
	if (m_isAffectedByGravity)
	{
		m_velocity.z += (9.8f * m_gravityScale) * deltaTime;
	}

	m_attachedSceneNode->translate(m_velocity * deltaTime);
}

void PhysicsBody::AddImpulse(Vector3 direction, float force)
{
	direction.normalise();
	direction *= force;
	m_velocity += direction;
}

bool PhysicsBody::GetIsAffectedByGravity()
{
	return m_isAffectedByGravity;
}

void PhysicsBody::SetIsAffectedByGravity(bool isAffectedByGravity)
{
	m_isAffectedByGravity = isAffectedByGravity;
}

float PhysicsBody::GetGravityScale()
{
	return m_gravityScale;
}

void PhysicsBody::SetGravityScale(float gravityScale)
{
	m_gravityScale = gravityScale;
}

Vector3 PhysicsBody::GetVelocity()
{
	return m_velocity;
}

void PhysicsBody::SetVelocity(Vector3 velocity)
{
	m_velocity = velocity;
}

float PhysicsBody::GetSpeed()
{
	return m_fSpeed;
}

float PhysicsBody::GetWeight()
{
	return m_weight;
}

void PhysicsBody::SetSpeed(float speed)
{
	m_fSpeed = speed;
}

void PhysicsBody::SetWeight(float weight)
{
	m_weight = weight;
}
