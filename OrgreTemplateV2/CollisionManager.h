#pragma once

#include "Ogre.h"
#include "GameObject.h"
#include "Collider.h"
using namespace Ogre;

/// Contains all collision functions.
/// 
/// Class with only static functions to be used as a manager for collision functions.
class CollisionManager
{
public:
	static bool PointAABBCollision(Vector3 point, CubeCollider* cube);
	static bool PointSphereCollision(Vector3 point, SphereCollider* sphere);
	static bool SquaredPointSphereCollision(Vector3 point, SphereCollider* sphere);
	static bool SquaredSphereSphereCollision(SphereCollider* sphere1, SphereCollider* sphere2);
	static bool SphereSphereCollision(SphereCollider* sphere1, SphereCollider* sphere2);
	static bool AABBSphereCollision(CubeCollider* cube, SphereCollider* sphere);
	/// Checks collision between and AABB and a sphere.
	/// @param cube is the AABB to be checked against.
	/// @param sphere is the sphere to be checked against.
	/// @returns Returns true if the two objects collide and false if not.
	/// @note This also sets the spheres IsColliding() variable to either true or false.
	/// @warning This will throw a bad allocation exception if sphere is not a PongBall type. The reason I leave it as a game object parameter is that if more spheres are later added into the game I can do future checking to see if their class types as spheres as well. This allows for more scaleability of this function.
	static bool SquaredAABBSphereCollision(CubeCollider* cube, SphereCollider* sphere);

	static bool AABBCollision(CubeCollider* cube1, CubeCollider* cube2);

};

