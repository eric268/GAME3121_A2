#pragma once
#include "GameObject.h"
#include "DoodlePlayer.h"

/// Class that manages the creation and movement of the background object 
/// 
/// This class encapsulates background object class which inhereits from GameObject. It manages its position based upon 
/// the player position. There are two background images that change Z postion based on player Z location
class BackgroundObject : public GameObject
{
	DoodlePlayer* doodlePlayerRef;
	float backgroundZExtent;
	float distanceToPlayer;
	Vector3 m_vBackgroundStartingPosition;

public:
	/// Default constructor for Background object
	/// 
	/// Initalizes all values to nullptr or 0
	BackgroundObject();

	/// Overloaded constructor for Background Object
	/// 
	/// This constructor initalizes a background object with parameters listed below.
	/// <param name="node"> Background Object Scene node that is created in main.cpp </param>
	/// <param name="scnMgr"> Pointer to scene manager so that Entities and Scene nodes can be correctly added and created</param>
	/// <param name="playerRef"> Reference to player character to know when to update the background position </param>
	/// <param name="idNumber">Unique id number for naming purposes</param>
	BackgroundObject(Ogre::SceneNode* node, Ogre::SceneManager* scnMgr, DoodlePlayer* playerRef, int idNumber);


	/// <Background object destructor>
	~BackgroundObject();

	/// <summary> Returns the Z extent value of the background object cube
	/// 
	/// This value is used when determining what new Z value the background object should have added to its current world postion</summary>
	/// <returns>Returns a float variable representing the background objects Z extent value</returns>
	float GetBackgroundZExtent();
	/// <summary>Gets the starting location of the background objects
	/// 
	/// This is important for restarting the game when background objects need to return to starting position</summary>
	/// <returns> a Vector3 value representing world starting postion</returns>
	Vector3 GetBackgroundStartingPosition();
	/// <summary> Sets the starting position of the background objects
	/// 
	/// This is important for future games where starting positon may vary</summary>
	/// <param name="startingPos">The Vector3 value that the starting position is to be set to</param>
	void SetBackgroundStartingPosition(Vector3 startingPos);

private:
	/// Overrides the bool GameObject::frameStarted(const Ogre::FrameEvent& evt) function found in GameObject.h
	/// 
	/// Checks for updates at the beginning of each frame for all Background objects. Is updates at a constant time across all hardware.
	/// @param evt Provides information regarding the time since the last event and the time since last update for each Background objects.
	/// @returns Returns true if next frame should be updated and false if next frame should not be updated and the game should be exited.
	bool frameStarted(const Ogre::FrameEvent& evt);

};

