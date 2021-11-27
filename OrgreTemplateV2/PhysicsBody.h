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
	float m_fSpeed;
	float m_weight;

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

	/// Returns game objects velocity.
	/// @returns Ogre::Vector3.
	Ogre::Vector3 GetVelocity();

	/// Changes game objects velocity.
	/// 
	/// Allows for game objects velocity to be initialized or set to different values.
	/// @param vel is the Ogre::Vector3 velocity that the game object will be set to.
	void SetVelocity(Ogre::Vector3 vel);
	/// Returns the speed of the game object.
	/// 
	/// The speed is what is used with direction to calculate objects velocity.
	/// @returns floating point value.
	float GetSpeed();

	/// Returns the weight of the object
	/// 
	/// This was initially used for detecting change in velocity when ball and paddle hit.
	/// Currently this is not important but still instantiated for future potential use.
	/// @returns Returns a floating number.
	float GetWeight();

	/// Changes game objects speed
	/// 
	/// Allows for game objects speed to be initialized or set to different values.
	/// @param speed is the floating point value the game objects speed will be set to.
	void SetSpeed(float speed);

	/// Changes the game objects weight
	/// 
	/// Allows for the game objects weight to be initialized or set to different values
	/// @param weight is the floating point value the game objects weight will be set too.
	void SetWeight(float weight);
};


