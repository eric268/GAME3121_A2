#include "CollisionManager.h"
#include "algorithm"

bool CollisionManager::PointAABBCollision(Vector3 point, CubeCollider* cube)
{
	return (point.x >= cube->GetMinX() && point.x <= cube->GetMaxX()) &&
		   (point.y >= cube->GetMinY() && point.y <= cube->GetMaxY()) &&
		   (point.z >= cube->GetMinZ() && point.z <= cube->GetMaxZ());
}

bool CollisionManager::PointSphereCollision(Vector3 point, SphereCollider* sphere)
{
	float distance = Math::Sqr((point.x - sphere->GetWorldPosition().x) * (point.x - sphere->GetWorldPosition().x) +
				     (point.y - sphere->GetWorldPosition().y) * (point.y - sphere->GetWorldPosition().y) +
					 (point.z - sphere->GetWorldPosition().z) * (point.z - sphere->GetWorldPosition().z));

	return distance < sphere->GetRadius();
}

bool CollisionManager::SquaredPointSphereCollision(Vector3 point, SphereCollider* sphere)
{
	float distance = (point.x - sphere->GetWorldPosition().x) * (point.x - sphere->GetWorldPosition().x) +
					 (point.y - sphere->GetWorldPosition().y) * (point.y - sphere->GetWorldPosition().y) +
					 (point.z - sphere->GetWorldPosition().z) * (point.z - sphere->GetWorldPosition().z);

	return distance < (sphere->GetRadius()* sphere->GetRadius());
}

bool CollisionManager::SquaredSphereSphereCollision(SphereCollider* sphere1, SphereCollider* sphere2)
{
	float distance = (sphere1->GetWorldPosition().x - sphere2->GetWorldPosition().x) * (sphere1->GetWorldPosition().x - sphere2->GetWorldPosition().x) +
					 (sphere1->GetWorldPosition().y - sphere2->GetWorldPosition().y) * (sphere1->GetWorldPosition().y - sphere2->GetWorldPosition().y) +
					 (sphere1->GetWorldPosition().z - sphere2->GetWorldPosition().z) * (sphere1->GetWorldPosition().z - sphere2->GetWorldPosition().z);

	return distance < (sphere1->GetRadius()* sphere1->GetRadius() + sphere2->GetRadius() * sphere2->GetRadius());

}

bool CollisionManager::SphereSphereCollision(SphereCollider* sphere1, SphereCollider* sphere2)
{
	float distance = Math::Sqr((sphere1->GetWorldPosition().x - sphere2->GetWorldPosition().x) * (sphere1->GetWorldPosition().x - sphere2->GetWorldPosition().x) +
						      (sphere1->GetWorldPosition().y - sphere2->GetWorldPosition().y) * (sphere1->GetWorldPosition().y - sphere2->GetWorldPosition().y) +
							  (sphere1->GetWorldPosition().z - sphere2->GetWorldPosition().z) * (sphere1->GetWorldPosition().z - sphere2->GetWorldPosition().z));

	return distance < (sphere1->GetRadius() + sphere2->GetRadius());
}

bool CollisionManager::AABBSphereCollision(CubeCollider* cube, SphereCollider* sphere)
{
	float x = std::max(cube->GetMinX(), std::min(sphere->GetWorldPosition().x, cube->GetMaxX()));
	float y = std::max(cube->GetMinY(), std::min(sphere->GetWorldPosition().y, cube->GetMaxY()));
	float z = std::max(cube->GetMinZ(), std::min(sphere->GetWorldPosition().z, cube->GetMaxZ()));

	float distance =Math::Sqr((x - sphere->GetWorldPosition().x) * (x - sphere->GetWorldPosition().x) +
		(y - sphere->GetWorldPosition().y) * (y - sphere->GetWorldPosition().y) +
		(z - sphere->GetWorldPosition().z) * (z - sphere->GetWorldPosition().z));

	return distance < sphere->GetRadius();
}

bool CollisionManager::SquaredAABBSphereCollision(CubeCollider* cube, SphereCollider* sphere)
{
	float x = std::max(cube->GetMinX(), std::min(sphere->GetWorldPosition().x, cube->GetMaxX()));
	float y = std::max(cube->GetMinY(), std::min(sphere->GetWorldPosition().y, cube->GetMaxY()));
	float z = std::max(cube->GetMinZ(), std::min(sphere->GetWorldPosition().z, cube->GetMaxZ()));

	float distance = (x - sphere->GetWorldPosition().x) * (x - sphere->GetWorldPosition().x) +
					 (y - sphere->GetWorldPosition().y) * (y - sphere->GetWorldPosition().y) +
					 (z - sphere->GetWorldPosition().z) * (z - sphere->GetWorldPosition().z);

	return distance < (sphere->GetRadius() * sphere->GetRadius());
}

bool CollisionManager::AABBCollision(CubeCollider* cube1, CubeCollider* cube2)
{
	return (cube1->GetMinX() <= cube2->GetMaxX() && cube1->GetMaxX() >= cube2->GetMinX()) &&
		   (cube1->GetMinY() <= cube2->GetMaxY() && cube1->GetMaxY() >= cube2->GetMinY()) &&
		   (cube1->GetMinZ() <= cube2->GetMaxZ() && cube1->GetMaxZ() >= cube2->GetMinZ());
}
