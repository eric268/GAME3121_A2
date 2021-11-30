#pragma once

#include "GameObject.h"
#include "CollisionManager.h"
#include "PhysicsBody.h"
#include "Platform.h"
#include "Collider.h"
#include "OgreLogManager.h"


/// The class which controls all main Players functionality
/// 
/// This class encapsulates and updates all variables and functions associated with the Doodle Player game object. It inherits from the Game Object class.
class DoodlePlayer : public GameObject
{
private:
	SceneNode* cameraNode;
	Camera* camera;
	bool m_bIsColliding;
	Ogre::Vector3 m_vDirection;
	float cameraPlayerDistanceLimit = 100.0f;
	float distanceFromCameraToPlayerZAxis;
	float playerDiedZValue;
	bool isFacingLeft;
	PhysicsBody* m_physicsBody;
	CubeCollider* m_cubeCollider;
	SphereCollider* m_sphereCollider;
	int m_iLivesRemaining;
	int m_iScore;
	bool m_bPointEarned;
	bool m_bLifeLost;
	Platform** m_platformArrayRef;
	int m_iNumberOfPlatforms;
	bool m_bGameOver;
	bool m_bGameWon;
	Log* m_gameLogRef;
	float m_fTotalGameTime;

public:
	//Constructor

	/// Default constructor for the Doodle Player game object
	DoodlePlayer();

	/// Overloaded constructor for the Doodle Player game object
	/// 
	/// This initializes all variables from either the inherited game object of Doodle Player specific variables.
	/// @param node This takes in a SceneNode pointer to the scene node created for the player.
	/// @param scnMgr This takes in a reference to the SceneManager pointer found in the MainInitalizer class in main.cpp.
	/// @param platformRef This is a Platform point array  reference that is used for collision detection between the player and platforms.
	/// @param gameLogRef This is a reference to the customer log created main. Used in Player class for logging time of game completion
	/// @param numPlatforms This is the maximum number of platforms in the game
	DoodlePlayer(Ogre::SceneNode* node, Ogre::SceneManager* scnMgr, Platform** platformRef, Log* gameLogRef, int numPlatforms);

	///Doodle Player Destructor
	///
	~DoodlePlayer();

	/// Returns whether or not the Player is colliding with a platform.
	/// 
	/// This value only returns true if the player is colliding with a platform, and returns false when it is not.
	/// @returns Returns a boolean.
	bool GetIsColliding();

	/// Sets the isColliding player variable.
	/// 
	/// Initializes or sets the isColliding ball variable to the parameter.
	/// @param colliding is a boolean that the isColliding ball variable will be set to.
	void SetIsColliding(bool colliding);

	/// Ensures the ball stays within the desired screen bounds
	/// 
	/// This function ensures that the ball will bounce off the top, left and right bounds of the window. If the ball falls into the protected area this function also returns it to its starting location and notifies the UIManager that it needs to update the remaining lives labels.
	void CheckBounds();

	/// Returns the score of the game
/// 
/// @returns Returns an integer value.
	int GetScore();

	/// Returns how many lives are remaining.
	///  
	/// @returns Returns an integer value.
	int GetLivesRemaining();

	/// Returns whether or not a life has been lost.
	///  
	/// This is used by the UIManager to know when to update the numeric label for number of lives remaining. This boolean is then set to true inside of the UIManager when the label has been successfully updated.
	/// @returns Returns a boolean value.
	bool GetLifeLost();

	/// Returns whether or not the score should be updated.
	///  
	/// This is used by the UIManager to know when to update the numeric label for players score.
	/// @returns Returns a boolean value.
	bool GetPointEarned();

	/// Increases the current players score by 1.
	///
	void IncrementScore();

	/// Decreases the number of remaining lives by 1.
	/// 
	void DecrementLivesRemaining();

	/// Sets the current score
	/// 
	/// Initializes or sets the current score to the parameter.
	/// @param score is an integer that the current score will be set to.
	void SetScore(int score);

	/// Sets the number of remaining lives.
	/// 
	/// Initializes or sets the number of remaining lives to the parameter.
	/// @param livesRemaining is an integer that the current lives remaining will be set to.
	void SetLivesRemaining(int livesRemaining);

	/// Sets the booleans for score update checking
	///  
	/// This boolean is set to true when the score has changed which tells the UIManager to update the score label that is displayed. It is set back to false once the UIManager has successfully updated that label.
	/// @param pEarned is an integer that the update score boolean will be set to.
	void SetPointEarned(bool pEarned);

	/// Sets the booleans for checking if the life remaining label should be updated.
	///  
	/// This boolean is set to true when a life has been lost which tells the UIManager to update the number of lives remaining that is displayed. It is set back to false once the UIManager has successfully updated that label.
	/// @param pEarned is an integer that the update score boolean will be set to.
	void SetLifeLabel(bool lifeLost);


	/// Overrides the bool GameObject::frameStarted(const Ogre::FrameEvent& evt) function found in GameObject.h
	/// 
	/// Checks for updates at the beginning of each frame for the player. Is updates at a constant time across all hardware.
	/// @param evt Provides information regarding the time since the last event and the time since last update for DoodlePlayer objects.
	/// @returns Returns true if next frame should be updated and false if next frame should not be updated and the game should be exited.
	bool frameStarted(const Ogre::FrameEvent& evt);

	/// This function is called when the player collides with a platform.
	/// 
	/// This function offsets any overlap between the colliding game objects. It is called inside CheckForCollisionWithPlatform()
	void CollisionWithPlayer(Platform* platform);

	/// <summary> This function checks for and handles collision with platforms
	/// 
	/// This function implements collision response when collision between the player and platform exists.
	/// It is also determines if the game has been won by checking if the player has collided with the final platform</summary>
	void CheckForCollisionWithPlatform();

	/// <summary> This function creates and attaches a camera to the player
	/// 
	/// Creates and initalizes the camera pointer and camera node variables instatiating them with correct values \n
	/// such as world position and direction</summary>
	/// @param scnMgr is a pointer to the SceneManager created in main.cpp which adds the camera correctly to the scene
	void CreatePlayerCamera(Ogre::SceneManager* scnMgr);

	/// <summary>Returns a pointer to a camera
	/// 
	/// Returns a pointer to the follow camera attached to the player</summary>
	/// @returns a variable of type Camera*
	Camera* GetPlayerCamera();

	/// <summary>Returns a pointer to the Camera Scene Node
	/// 
	/// Gets the pointer which owns the Scene node that the player follow camera is attached to</summary>
	/// @return returns a variable of type SceneNode*
	SceneNode* GetCameraNode();

	/// <summary> Updates camera position based on player position
	/// 
	/// This function allows camera movement when player has moved approximately halfway up on the screen</summary>
	/// @param FrameEvent& so that camera movement is fixed to player movement updates
	void UpdateCameraPosition(const Ogre::FrameEvent& evt);

	/// <summary> Sets boolean of player direction
	/// 
	/// Sets the boolean of the variable that tracks whether the player is facing left or right</summary>
	/// @param Takes a boolean param which the facing direction boolean is then set to
	void SetIsFacingLeft(bool dir);

	/// <summary> Gets the boolean value of player direction
	/// 
	/// Returns true if the player is facing left and false if the player is facing right</summary>
	bool GetIsFacingLeft();
	/// <summary> Rotates player based on input
	/// 
	/// Flips the players left or right direction if opposite input is pressed</summary>
	/// @param Takes a char input with responses when A or D is inputted
	void UpdatePlayerDirection(char input);

	/// <summary> Returns a pointer to the players Physics Body
	/// 
	/// Returns the players physics body which handles all physics related functionality</summary>
	/// @returns variable of type PhysicsBody*
	/// @see PhysicsBody.h
	PhysicsBody* GetPhysicsBody();

	/// <summary> Returns a pointer to the players cube collider
	/// 
	/// This handles all collision related functionality for the player</summary>
	/// @returns variable of type CubeCollider*
	/// @see Collider.h
	CubeCollider* GetCubeCollider();

	/// <summary> Handles reponse to player hitting platform
	/// 
	/// This function adds an impulse to the player after collision with a platform</summary>
	/// @see PhysicsBody.h
	void PlayerHitPlatform();

	/// <summary>Sets the players game over variable
	/// 
	/// This function is used to broadcast and to stop certain updates when the game is over. \n 
	/// The game can end from either the player reaching the top of the platforms or losing all lives</summary>
	/// @param Boolean the game over variable is set to
	void SetGameOver(bool m_bGameOver);

	/// <summary>Sets the players game won boolean 
	/// 
	/// Sets the variable which is used for text display of whether game lost or won</summary>
	/// @param GameWon the game won variable is set to
	void SetGameWon(bool m_bGameWon);

	/// <summary> Gets the players GameOver boolean variable
	/// 
	/// @returns a variable of type bool
	bool GetGameOver();

	/// <summary> Gets the players GameWon boolean variable
	/// 
	/// @returns a variable of type bool
	bool GetGameWon();

	/// <summary> Sets the player and platforms visiblity to false
	/// 
	/// This is called when the game is over</summary>
	void HidePlayerAndPlatforms();

	/// <summary>Sets the player and platforms visibility to true
	/// 
	/// This is called in main.cpp when the game is restarted </summary>
	/// @see RestartGame()
	void ResetPlayerAndPlatforms();


};

