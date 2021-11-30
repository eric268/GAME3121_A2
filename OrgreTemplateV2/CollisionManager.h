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
	/// <summary>Checks for collision between a point and cube
	/// 
	/// Returns true if collision occurs and false if not</summary>
	/// <param name="point">Vector3 world position of the point</param>
	/// <param name="cube">Pointer to the cube collider</param>
	/// <returns>a boolean value</returns>
	static bool PointAABBCollision(Vector3 point, CubeCollider* cube);

	/// <summary>Checks for collision between a point and sphere
	/// 
	/// Returns true if collision occurs and false if not</summary>
	/// <param name="point">Vector3 world position of the point</param>
	/// <param name="sphere">Pointer to the sphere collider</param>
	/// <returns>a boolean value</returns>
	static bool PointSphereCollision(Vector3 point, SphereCollider* sphere);

	/// <summary>Function which determines collision between point and sphere
	/// 
	/// Function does a squared collison check for determining collision between a point and a sphere</summary>
	/// <param name="point">Vector3 world position of the point</param>
	/// <param name="sphere">Pointer to the sphere collider</param>
	/// <returns>a boolean value</returns>
	/// @note this method is the recommended method for PointSphere collision detection due to no Sqrt cost
	static bool SquaredPointSphereCollision(Vector3 point, SphereCollider* sphere);

	/// <summary>Function which checks collision between two spheres
	/// 
	/// This function does a squared distance check between the distance and radius of two spheres to determine collision detection. Returns true if collision occurs and false if not</summary>
	/// <param name="sphere1">Pointer to first sphere collider</param>
	/// <param name="sphere2">Pointer to second sphere collider</param>
	/// <returns>a bool value</returns>
	/// @note this method is the recommended method for Sphere Sphere collision detection due to no Sqrt cost
	static bool SquaredSphereSphereCollision(SphereCollider* sphere1, SphereCollider* sphere2);

	/// <summary>Function which checks collision between two spheres
	/// 
	/// This function does collision detection between two spheres. Returns true if collision occurs and false if not</summary>
	/// <param name="sphere1">Pointer to first sphere collider</param>
	/// <param name="sphere2">Pointer to second sphere collider</param>
	/// <returns>a bool value</returns>
	static bool SphereSphereCollision(SphereCollider* sphere1, SphereCollider* sphere2);

	/// Checks collision between a cube and a sphere.
	/// @param cube is the cube collider to be checked against.
	/// @param sphere is the sphere collider to be checked against.
	/// @returns Returns true if the two objects collide and false if not.
	static bool AABBSphereCollision(CubeCollider* cube, SphereCollider* sphere);

	/// <summary>Checks for collision between a cube and sphere
	/// 
	/// <param name="cube">Ponter to cube collider</param>
	/// <param name="sphere">Pointer to sphere collider</param>
	/// <returns>true if collision occurs and false if not</returns>
	/// @note this method is the recommended method for Cube Sphere collision detection due to no Sqrt cost
	static bool SquaredAABBSphereCollision(CubeCollider* cube, SphereCollider* sphere);

	/// <summary>Checks for collision between a cube and sphere
	/// 
	/// <param name="cube">Ponter to cube collider</param>
	/// <param name="sphere">Pointer to sphere collider</param>
	/// <returns>true if collision occurs and false if not</returns>
	static bool AABBCollision(CubeCollider* cube1, CubeCollider* cube2);
};

