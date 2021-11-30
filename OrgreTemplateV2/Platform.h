#pragma once

#include "GameObject.h"
#include "Collider.h"

/// The class which controls all Platform functionality
/// 
/// This class encapsulates and updates all variables and functions associated with the Platform game object. It inherits from the Game Object class.
class Platform : public GameObject
{
private:
	int m_iPlatformIDNumber;
	bool m_bPointEarned;
	CubeCollider* m_cubeCollider;
public:
	/// Default constructor for the Platform.
	/// 
	/// Initializes all values to 0 or nullptr.
	Platform();

	/// Overloaded constructor for the Platform class.
	/// 
	/// This initializes and creates the player Platform.
	/// @param player This takes in a SceneNode pointer to the scene node created for the Platform game object.
	/// @param SceneManager* This takes in a reference to the SceneManager pointer found in the MainInitalizer class in main.cpp.
	Platform(Ogre::SceneNode* player, Ogre::SceneManager* scnMgr, int platformIDNumber);

	/// Destructor for the Platform class.
	///
	~Platform();

	/// Overrides the bool GameObject::frameStarted(const Ogre::FrameEvent& evt) function found in GameObject.h
	/// 
	/// Checks for updates at the beginning of each frame for all Platform objects. Is updates at a constant time across all hardware.
	/// @param evt Provides information regarding the time since the last event and the time since last update for each Platform object.
	/// @returns Returns true if next frame should be updated and false if next frame should not be updated and the game should be exited.
	bool frameStarted(const Ogre::FrameEvent& evt);

	/// <summary>Gets the Platforms collider
	/// 
	/// This function returns a pointer to the platforms cube collider which is used for collision detection\n
	/// between the player and platforms</summary>
	/// <returns> a pointer to a CubeCollider variable</returns>
	/// @see Collider.h
	CubeCollider* GetCubeCollider();

	/// <summary>Sets the boolean of PointEarned
	/// 
	/// This variable is used to determine if the player has already collided with the platform and therefore already recieved a point</summary>
	/// <param name="pEarned"> boolean the platforms point earned variable is set to</param>
	void SetPointEarned(bool pEarned);

	/// <summary> Gets the players point earned boolean variable
	/// 
	/// <returns>a variable of type bool</returns>
	bool GetPointEarned();
};


