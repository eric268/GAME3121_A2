#pragma once

#include "GameObject.h"
#include "CollisionManager.h"
#include "PhysicsBody.h"
#include "Platform.h"
#include "Collider.h"
#include "OgreLogManager.h"


/// The class which controls all Pong Ball functionality
/// 
/// This class encapsulates and updates all variables and functions associated with the pong ball game object. It inherits from the Game Object class.
class DoodlePlayer : public GameObject
{
private:
	SceneNode* cameraNode;
	Camera* camera;
	bool m_bIsColliding;
	Ogre::Vector3 m_vDirection;
	float m_radius;
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

	/// Default constructor for the PongBall game object.
	/// 
	DoodlePlayer();

	/// Overloaded constructor for the PongBall game object
	/// 
	/// This initializes all variables from either the inherited game object of PongBall specific variables.
	/// @param node This takes in a SceneNode pointer to the scene node created for the player paddle.
	/// @param scnMgr This takes in a reference to the SceneManager pointer found in the MainInitalizer class in main.cpp.
	/// @param pRef This is a PongPaddle reference that is used for collision detection between the player paddle and the ball.
	/// @note The ball is the game object that handles collision between the paddle and it's self. This is because their is no collision response for the paddle, only for the ball.
	DoodlePlayer(Ogre::SceneNode* node, Ogre::SceneManager* scnMgr, Platform** platformRef, Log* gameLogRef, int numPlatforms);

	///PongBall Destructor
	///
	~DoodlePlayer();

	/// Returns whether or not the ball is colliding.
	/// 
	/// This value only returns true if the ball is colliding with the player paddle, and returns false when it is not.
	/// @returns Returns a boolean.
	bool GetIsColliding();

	/// Sets the isColliding ball variable.
	/// 
	/// Initializes or sets the isColliding ball variable to the parameter.
	/// @param colliding is a boolean that the isColliding ball variable will be set to.
	void SetIsColliding(bool colliding);

	/// Returns whether the radius of the PongBall game object.
	///
	/// @returns Returns a floating point value.
	float GetRadius();


	/// Sets the radius ball variable.
	/// 
	/// Initializes or sets the radius of the PongBall game object. This value is usually based upon the scale of the ball as well as its initial mesh extends.
	/// @param radius is a floating point value that ball radius variable will be set to.
	void SetRadius(float radius);

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
	/// Checks for updates at the beginning of each frame for all Pong Ball objects. Is updates at a constant time across all hardware.
	/// @param evt Provides information regarding the time since the last event and the time since last update for each Pong Ball objects.
	/// @returns Returns true if next frame should be updated and false if next frame should not be updated and the game should be exited.
	bool frameStarted(const Ogre::FrameEvent& evt);

	/// This function is called when the player collides with a platform.
	/// 
	/// This function offsets any overlap between the colliding game objects. It then calls a VelocityAfterPaddleCollision() to update the balls velocity.
	void CollisionWithPlayer(Platform* platform);

	void CheckForCollisionWithPlatform();

	void CreatePlayerCamera(Ogre::SceneManager* scnMgr);

	Camera* GetPlayerCamera();

	SceneNode* GetCameraNode();

	void UpdateCameraPosition(const Ogre::FrameEvent& evt);

	void SetIsFacingLeft(bool dir);
	bool GetIsFacingLeft();
	void UpdatePlayerDirection(char input);

	PhysicsBody* GetPhysicsBody();
	CubeCollider* GetCubeCollider();

	void PlayerHitPlatform();

	void SetGameOver(bool m_bGameOver);
	void SetGameWon(bool m_bGameWon);
	bool GetGameOver();
	bool GetGameWon();

	void HidePlayerAndPlatforms();
	void ResetPlayerAndPlatforms();


};

