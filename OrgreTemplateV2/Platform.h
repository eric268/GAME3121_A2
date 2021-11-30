#pragma once

#include "GameObject.h"
#include "Collider.h"

/// The class which controls all Pong Paddle functionality
/// 
/// This class encapsulates and updates all variables and functions associated with the Pong Paddle game object. It inherits from the Game Object class.
class Platform : public GameObject
{
private:
	int m_iPlatformIDNumber;

	CubeCollider* m_cubeCollider;
public:
	/// Default constructor for the PongPaddle.
	/// 
	/// Initializes all values to 0 or nullptr.
	Platform();

	/// Overloaded constructor for the PongPaddle class.
	/// 
	/// This initializes and creates the player PongPaddle.
	/// @param player This takes in a SceneNode pointer to the scene node created for the player paddle.
	/// @param SceneManager* This takes in a reference to the SceneManager pointer found in the MainInitalizer class in main.cpp.
	Platform(Ogre::SceneNode* player, Ogre::SceneManager* scnMgr, int platformIDNumber);

	/// Destructor for the PongPaddle class.
	///
	~Platform();

	/// Overrides the bool GameObject::frameStarted(const Ogre::FrameEvent& evt) function found in GameObject.h
	/// 
	/// Checks for updates at the beginning of each frame for all Pong Paddle objects. Is updates at a constant time across all hardware.
	/// @param evt Provides information regarding the time since the last event and the time since last update for each Pong Paddle object.
	/// @returns Returns true if next frame should be updated and false if next frame should not be updated and the game should be exited.
	bool frameStarted(const Ogre::FrameEvent& evt);

	CubeCollider* GetCubeCollider();
};


