#include "PhysicsComponent.h"

#include "SceneObject.h"
#include "PhysicsSystem.h"

#include "Matrix4x4.h"

PhysicsComponent::PhysicsComponent(SceneObject* owner) : Component("RigidBody", ComponentID::PHYSICS, owner)
{
	PhysicsSystem::Get()->RegisterComponent(this);
	reactphysics3d::PhysicsCommon* physicsCommon = PhysicsSystem::Get()->GetPhysicsCommon();
	reactphysics3d::PhysicsWorld* physicsWorld = PhysicsSystem::Get()->GetPhysicsWorld();


	Vector3D scale = m_Owner->getTransform()->getScale();
	reactphysics3d::Transform transform;
	//transform.setFromOpenGL(m_Owner->getTransform()->getWorldMatrix().m_mat);

	reactphysics3d::BoxShape* boxShape = physicsCommon->createBoxShape(reactphysics3d::Vector3(scale.x/2, scale.y/2, scale.z/2));

	this->m_Rb = physicsWorld->createRigidBody(transform);
	this->m_Rb->addCollider(boxShape, transform);
	this->m_Rb->updateMassPropertiesFromColliders();
	this->m_Rb->setMass(m_Mass);
	this->m_Rb->setType(reactphysics3d::BodyType::DYNAMIC);

	transform = this->m_Rb->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	Matrix4x4 calcMatrix;
	calcMatrix.setValues(matrix);
	m_Owner->getTransform()->setWorldMatrix(calcMatrix);
}

PhysicsComponent::~PhysicsComponent()
{
	delete m_Rb;
}

void PhysicsComponent::update()
{
	std::cout << "du";

	// COPY THE RIGID BODIES TRANSFORMS
	const reactphysics3d::Transform rb_Transform = m_Rb->getTransform();
	float matrix[16];
	rb_Transform.getOpenGLMatrix(matrix);

	Matrix4x4 calcMatrix;
	calcMatrix.setValues(matrix);
	m_Owner->getTransform()->setWorldMatrix(calcMatrix);

	std::cout << rb_Transform.getPosition().x << ", " << rb_Transform.getPosition().y << ", " << rb_Transform.getPosition().z << std::endl;
}

reactphysics3d::RigidBody* PhysicsComponent::GetRB()
{
	return m_Rb;
}