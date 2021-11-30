#pragma once
#include "Ogre.h"
using namespace Ogre;

/// <summary> Class which encapsulates all physics functionality
/// 
/// This class manages and updates all physics related measurements or responses</summary>
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
	/// <summary>Default Physics body constructor
	/// 
	/// Values are initalized to either 0 or nukllptr</summary>
	PhysicsBody();

	/// <summary> Overloaded Physics body constructor
	/// 
	/// @note Important to note that this constructor has to be used if you wish for the Physics body to be attached to the correct game object
	/// <param name="attachedBodyNode">Pointer to SceneNode of parent game object</param>
	PhysicsBody(SceneNode* attachedBodyNode);

	///Physics body destructor
	~PhysicsBody();

	/// <summary>Update function for movement and gravity updates
	/// 
	/// This function handles all movement of the parent game object through the attached SceneNode pointer</summary>
	/// <param name="deltaTime">This is the change in time from last Frame and should be implemented in the frameStarted(const Ogre::FrameEvent& evt) function of each game object(</param>
	/// @warning If this function is not called correctly it will result in no physics updates for the attached game object including *movement*
	void Update(float deltaTime);

	/// <summary>Function adds an impulse to a physics body
	/// 
	/// This function adds a one time impulse in any direction or amount to a physics body</summary>
	/// <param name="direction">The direction of the impulse</param>
	/// <param name="force">The force of the impulse</param>
	/// @note the direction is normalized in the function
	void AddImpulse(Vector3 direction, float force);

	/// <summary>Returns whether the physics body is affected by gravity
	/// 
	/// <returns>a boolean variable</returns>
	bool GetIsAffectedByGravity();

	/// <summary>Sets whether the physics body is affected by gravity
	/// 
	/// @note while this will stop gravity from affected a physics body other physics methods like AddImpulse() or velocity related changes will still take place
	/// <param name="m_isAffectedByGravity">sets IsAffected by gravity to parameter</param>
	void SetIsAffectedByGravity(bool m_isAffectedByGravity);

	/// <summary>Returns the gravity scale multipler
	/// 
	/// This variable acts as a multiplier to the current gravity of 9.8 which affects physics bodies.\n A higher
	/// gravity scale increases gravity while a lower gravity scale reduces the effects of gravity</summary>
	/// <returns>a floating point variable</returns>
	float GetGravityScale();

	/// <summary>Sets the gravity scale of the Physics body
	/// 
	/// <param name="gravityScale">Sets the gravity scaling float variable to the paramters</param>
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


