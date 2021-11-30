#pragma once
#include "Ogre.h"

using namespace Ogre;

/// <summary>An enum for Collider Types
/// 
/// This enum is used to help easily determine which type of collider a game object has</summary>
enum ColliderType
{
	NONE = -1,
	CUBE,
	SPHERE,
	NUM_COLLIDER_TYPES,
};

/// <summary>Base class for all collider types
/// 
/// This class encapsulates all fundamental aspects and variables of game object colliders</summary>
class Collider
{
public:
	/// <summary>Default Constructor
	/// 
	/// Initalizes all variables to nullptr or 0</summary>
	Collider();
	/// <summary>Overloaded Collider constructor
	/// 
	/// Initalizes variables to a base inital amount.</summary>
	/// <param name="attachedSceneNode"> reference to the scene node to the game object that this collider is being attached too</param>
	/// @note This class should rarly be used please use a child collider class
	Collider(SceneNode* attachedSceneNode);

	///Collider Destructor
	~Collider();

	/// <summary>Sets the collider type
	/// 
	/// Sets the type variable to a Collider Type enum</summary>
	/// <param name="colliderType">enum for determining collider type to set collider type to</param>
	void SetColliderType(ColliderType colliderType);

	/// <summary>Returns enum which shows which type of Collider the attached collider is
	/// 
	/// </summary>
	/// <returns>a variable of type Collider Type</returns>
	ColliderType GetColliderType();

	/// <summary>Sets the isTrigger boolean 
	/// 
	/// This variable is used to determine whether or not collision response should occcur</summary>
	/// <param name="isTrigger">boolean value variable should be set to</param>
	void SetIsTrigger(bool isTrigger);

	/// <summary>Returns isTrigger boolean value
	/// 
	/// </summary>
	/// <returns>variable of type boolean</returns>
	bool GetIsTrigger();

	/// <summary>Sets the local position Vector3 value
	/// 
	/// Local postion variable is used to determine any offset the collider has in relation to attached game object</summary>
	/// <param name="localPosition">Vector3 value that localPosition should be set to</param>
	void SetLocalPosition(Ogre::Vector3 localPosition);

	/// <summary>Returns the Vector3 local position variable
	/// 
	/// This variable is used to determine collider offset in relation to attached game object</summary>
	/// <returns>variable of type Vector3</returns>
	Ogre::Vector3 GetLocalPosition();

	/// <summary>Attaches Collider to SceneNode
	/// 
	/// This function attaches the collider to the game object scene node</summary>
	/// <param name="attachedSceneNode">SceneNode pointer that collider should be attached to</param>
	/// @note this is important for determining world position of collider when parent game object is moving 
	void SetAttachedSceneNode(SceneNode* attachedSceneNode);

	/// <summary>Returns a pointer that the SceneNode that the collider is attached to
	///
	/// <returns>pointer variable of type SceneNode</returns>
	SceneNode* GetAttachedSceneNode();

	/// <summary>Returns the world position of the collider
	/// 
	/// This function uses the parent game objects SceneNode to determine world position along with colliders localPosition</summary>
	/// <returns>variable of type Vector3</returns>
	Vector3 GetWorldPosition();

private:
	ColliderType m_colliderType;
	bool m_isTrigger;
	Ogre::Vector3 m_localPosition;
	Ogre::SceneNode* m_attachedSceneNode;
};

/// <summary>Collider class that encapsulates all cube collider functionality
/// 
/// This class inheretes from Collider base class. It is specifically designed for all cube collider functionality and requirements</summary>
class CubeCollider : public Collider
{
public:
	/// <summary>Cube collider overloaded constructor
	/// 
	/// This class initalizes some base values but most box extents need to be initalized by user</summary>
	/// <param name="attachedSceneNode">Pointer to parent game objects SceneNode</param>
	CubeCollider(SceneNode* attachedSceneNode);

	/// Cube Coollider Destructor
	~CubeCollider();

	/// <summary>Gets the cubes X Extent value
	/// 
	/// This value is primarily used for determining size of collider</summary>
	/// <returns>a variable of type float</returns>
	float GetXExtent();

	/// <summary>Gets the cubes Y Extent value
	/// 
	/// This value is primarily used for determining size of collider</summary>
	/// <returns>a variable of type float</returns>
	float GetYExtent();

	/// <summary>Gets the cubes Z Extent value
	/// 
	/// This value is primarily used for determining size of collider</summary>
	/// <returns>a variable of type float</returns>
	float GetZExtent();

	/// <summary>Sets the cube colliders X Extent Variable
	/// 
	/// <param name="length">float value that the extent will be set to</param>
	void SetXExtent(float length);

	/// <summary>Sets the cube colliders Y Extent Variable
	/// 
	/// <param name="length">float value that the extent will be set to</param>
	void SetYExtent(float length);

	/// <summary>Sets the cube colliders Z Extent Variable
	/// 
	/// <param name="length">float value that the extent will be set to</param>
	void SetZExtent(float length);

	/// <summary>Sets all extents to one value
	/// 
	/// <param name="length">Single float value that all cube extents will be set to</param>
	void SetAllExtent(float length);

	/// <summary>Function which sets extents individually to values contained in Vector3
	/// 
	/// <param name="vec">is the Vector3 value that the cube extents will be set to</param>
	void SetAllExtent(Vector3 vec);

	/// <summary>Gets all the extent values of the cube collider
	/// 
	/// <returns>a variable of type Vector3</returns>
	Vector3 GetExtents();

	/// <summary>Creates a game object representing the bounding box
	/// 
	/// This function is used to debug or visualize the created cube bounding box when attached to a game object</summary>
	/// <param name="scnMgr">Pointer to SceneManager so that the created game object can be added to the scene</param>
	/// <param name="idNumber">unique integer for ID purposes</param>
	/// @note this is only designed for debugging purposes
	void CreateBoundingBox(Ogre::SceneManager* scnMgr, int idNumber);

	/// <summary>Moves the created game object bounding box
	/// 
	/// This function is used for debugging or to visualize the created cube bounding box when the parent game object moves in the scene</summary>
	/// <param name="pos">Vector3 postioin that the box should be set to</param>
	void TranslateBoundingBox(Vector3 pos);

	/// <summary>Returns the min X value of Collider
	/// 
	/// This function returns the world position of the minimum X value the collider has</summary>
	/// <returns>a floating point variable</returns>
	/// @note this is used primarily in collision detection
	///  @see CollisionManager.h
	float GetMinX();

	/// <summary>Returns the max X value of Collider
	/// 
	/// This function returns the world position of the maximum X value the collider has</summary>
	/// <returns>a floating point variable</returns>
	/// @note this is used primarily in collision detection
	///  @see CollisionManager.h
	float GetMaxX();

	/// <summary>Returns the min Y value of Collider
	/// 
	/// This function returns the world position of the minimum Y value the collider has</summary>
	/// <returns>a floating point variable</returns>
	/// @note this is used primarily in collision detection
	///  @see CollisionManager.h
	float GetMinY();

	/// <summary>Returns the max Y value of Collider
	/// 
	/// This function returns the world position of the maximum Y value the collider has</summary>
	/// <returns>a floating point variable</returns>
	/// @note this is used primarily in collision detection
	///  @see CollisionManager.h
	float GetMaxY();

	/// <summary>Returns the min Z value of Collider
	/// 
	/// This function returns the world position of the minimum Z value the collider has</summary>
	/// <returns>a floating point variable</returns>
	/// @note this is used primarily in collision detection
	///  @see CollisionManager.h
	float GetMinZ();

	/// <summary>Returns the max Z value of Collider
	/// 
	/// This function returns the world position of the maximum Z value the collider has</summary>
	/// <returns>a floating point variable</returns>
	/// @note this is used primarily in collision detection
	///  @see CollisionManager.h
	float GetMaxZ();

private:
	SceneNode* m_boundingBoxNode;
	bool boundingBoxNodeCreated;

	float xExtent;
	float yExtent;
	float zExtent;

	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;
};

	/// <summary>Collider class that encapsulates all sphere collider functionality
	/// 
	/// This class inheretes from Collider base class. It is specifically designed for all sphere collider functionality and requirements</summary>
class SphereCollider: public Collider
{
public:
	/// <summary>Overloaded Sphere Collider constructor
	/// 
	/// Initalizes variables to a base inital amount.</summary>
	/// <param name="attachedSceneNode"> reference to the scene node to the game object that this collider is being attached to</param>
	SphereCollider(SceneNode* attachedSceneNode);

	///Sphere Collider Destructor
	~SphereCollider();

	/// <summary>Returns the radius of the sphere collider
	/// 
	/// <returns>a floating point variable</returns>
	float GetRadius();

	/// <summary>Sets the radius of the sphere collider
	/// 
	/// <param name="radius">float value that radius will be set to</param>
	void SetRadius(float radius);

	/// <summary>Creates a game object representing the sphere collider
	/// 
	/// This function is used to debug or visualize the createdsphere collider when attached to a game object</summary>
	/// <param name="scnMgr">Pointer to SceneManager so that the created game object can be added to the scene</param>
	/// <param name="idNumber">unique integer for ID purposes</param>
	/// @note this is only designed for debugging purposes
	void CreateSphericalBoundingBox(SceneManager* scnMgr,int idNumber);

	/// <summary>Moves the created spherical game object
	/// 
	/// This function is used for debugging or to visualize the sphere collider when the parent game object moves in the scene</summary>
	/// <param name="pos">Vector3 postioin that the box should be set to</param>
	void TranslateSphericalBoundingBox(Vector3 pos);

private:
	float m_radius;
	SceneNode* sphericalBoundingBoxNode;
	bool boundingBoxNodeCreated;
};
