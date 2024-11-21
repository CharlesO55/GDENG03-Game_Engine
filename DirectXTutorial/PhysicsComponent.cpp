#include "PhysicsComponent.h"

#include "SceneObject.h"
#include "PhysicsSystem.h"

#include "Debugger.h"
#include "Matrix4x4.h"

PhysicsComponent::PhysicsComponent(SceneObject* owner, reactphysics3d::BodyType RB_TYPE) : Component("RigidBody", ComponentID::PHYSICS, owner)
{
	PhysicsSystem::Get()->RegisterComponent(this);
	reactphysics3d::PhysicsCommon* physicsCommon = PhysicsSystem::Get()->GetPhysicsCommon();
	reactphysics3d::PhysicsWorld* physicsWorld = PhysicsSystem::Get()->GetPhysicsWorld();


	//	READ THE CURRENT TRANSFORM
	Vector3D scale = m_Owner->getTransform()->getScale();
	reactphysics3d::Transform transform;	
	
	// BUGGY.
	//transform.setFromOpenGL(m_Owner->getTransform()->getWorldMatrix().Flatten());
	// TEMP
	transform.setToIdentity();


	reactphysics3d::BoxShape* boxShape = physicsCommon->createBoxShape(reactphysics3d::Vector3(scale.x/2, scale.y/2, scale.z/2));

	m_Owner->getTransform()->getWorldMatrix().PrintMatrix();
	/*float test[16];
	transform.getOpenGLMatrix(test);
	Debugger::PrintMatrix(test);*/

	this->m_Rb = physicsWorld->createRigidBody(transform);
	this->m_Rb->addCollider(boxShape, transform);
	this->m_Rb->updateMassPropertiesFromColliders();
	this->m_Rb->setMass(m_Mass);
	this->m_Rb->setType(RB_TYPE);


	CopyRBTransform();
}

PhysicsComponent::~PhysicsComponent()
{
	delete m_Rb;
}

void PhysicsComponent::update()
{
	//const reactphysics3d::Transform rb_Transform = m_Rb->getTransform();
	//Debugger::PrintVector(rb_Transform.getPosition());

	CopyRBTransform();
}

reactphysics3d::RigidBody* PhysicsComponent::GetRB()
{
	return m_Rb;
}

void PhysicsComponent::CopyRBTransform()
{
	// COPY RB TRANSFORM TO OBJ
	const reactphysics3d::Transform& transform = this->m_Rb->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	Matrix4x4 calcMatrix;
	calcMatrix.setValues(matrix);
	m_Owner->getTransform()->setWorldMatrix(calcMatrix);
}