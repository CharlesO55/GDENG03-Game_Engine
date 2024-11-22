#include "PhysicsComponent.h"

#include "SceneObject.h"
#include "PhysicsSystem.h"

#include "Debugger.h"
#include "Matrix4x4.h"

#include <DirectXMath.h>


PhysicsComponent::PhysicsComponent(SceneObject* owner, reactphysics3d::BodyType RB_TYPE) : Component("RigidBody", ComponentID::PHYSICS, owner)
{
	PhysicsSystem::Get()->RegisterComponent(this);
	reactphysics3d::PhysicsCommon* physicsCommon = PhysicsSystem::Get()->GetPhysicsCommon();
	reactphysics3d::PhysicsWorld* physicsWorld = PhysicsSystem::Get()->GetPhysicsWorld();
	reactphysics3d::Transform startingTransform;	
	
	// BUGGY.
	try {
		float* values = m_Owner->getTransform()->getWorldMatrix().Flatten().data();
		startingTransform.setFromOpenGL(values);
		
		//startingTransform.setToIdentity();
		//startingTransform.setPosition(reactphysics3d::Vector3(values[12], values[13], values[14]));

		
		DirectX::XMMATRIX dx_matrix = m_Owner->getTransform()->DX_Matrix;
		DirectX::XMVECTOR dx_quat = DirectX::XMQuaternionRotationMatrix(dx_matrix);
		
		std::cout << "\nDX QUAT: (" << DirectX::XMVectorGetX(dx_quat) << " , " << DirectX::XMVectorGetY(dx_quat) << " , " << DirectX::XMVectorGetZ(dx_quat) << " , " << DirectX::XMVectorGetW(dx_quat) << ")\n";
		
		startingTransform.setOrientation(reactphysics3d::Quaternion(
			DirectX::XMVectorGetX(dx_quat),
			DirectX::XMVectorGetY(dx_quat),
			DirectX::XMVectorGetZ(dx_quat),
			DirectX::XMVectorGetW(dx_quat)
		));

		
		//std::cout << "\nOPENGL:\n\t" << startingTransform.to_string() << std::endl;

		if (!startingTransform.isValid()) {
			std::cout << "\nPos: " << startingTransform.getPosition().isFinite();
			std::cout << "\nOriFinite: " << startingTransform.getOrientation().isFinite();
			std::cout << "\nOriUnit: " << startingTransform.getOrientation().isUnit();
			Debugger::Error("Invalid RB transforms.");
		}
	}
	catch (...) {
		startingTransform.setToIdentity();
	}
	
	Vector3D scale = m_Owner->getTransform()->getScale();
	reactphysics3d::BoxShape* boxShape = physicsCommon->createBoxShape(reactphysics3d::Vector3(scale.x/2, scale.y/2, scale.z/2));

	m_Owner->getTransform()->getWorldMatrix().PrintMatrix();

	this->m_Rb = physicsWorld->createRigidBody(startingTransform);
	this->m_Rb->addCollider(boxShape, startingTransform);
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