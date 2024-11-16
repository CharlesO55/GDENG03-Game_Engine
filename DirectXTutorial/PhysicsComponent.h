#pragma once
#include "Component.h"

#include <vector>
#include <reactphysics3d/reactphysics3d.h>

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(SceneObject* owner);
	~PhysicsComponent();

	void update() override;

	reactphysics3d::RigidBody* GetRB();

private:
	float m_Mass = 1000;
	reactphysics3d::RigidBody* m_Rb;
};

