#include "Transformation.h"

#include "EngineState.h"
#include "SceneObject.h"

Transformation::Transformation(SceneObject* owner) : Component("Transformation", ComponentID::TRANSFORMATION, owner)
{
	m_WorldMatrix.setIdentity();
	DX_Matrix = DirectX::XMMatrixIdentity();
}

Transformation::~Transformation()
{
}
void Transformation::move(const Vector3D deltaPos)
{
	m_pos = m_pos + deltaPos;
}

void Transformation::scale(const Vector3D deltaScale)
{
	m_scale = m_scale + deltaScale;
}

void Transformation::rotate(const Vector3D deltaRot)
{
	m_rot = m_rot + deltaRot;
}

void Transformation::setPosition(const Vector3D position)
{
	m_pos = position;
}

void Transformation::setScale(const Vector3D scale)
{
	m_scale = scale;
}

void Transformation::setRotation(const Vector3D rotation)
{
	m_rot = rotation;
}

void Transformation::setWorldMatrix(const Matrix4x4 matrix)
{
	m_WorldMatrix = matrix;

	m_pos = m_WorldMatrix.getTranslation();
	m_rot = m_WorldMatrix.getEulerAngles();
	m_scale = m_WorldMatrix.getScale();
}

const Vector3D Transformation::getPosition()
{
	return m_pos;
}

const Vector3D Transformation::getScale()
{
	return m_scale;
}

const Vector3D Transformation::getRotation()
{
	return m_rot;
}



void Transformation::update()
{
	Matrix4x4 temp;

	//Reset
	m_WorldMatrix.setIdentity();
	
	//Scale
	m_WorldMatrix.setScale(m_scale);

	//Rotate
	temp.setIdentity();
	temp.setRotationZ(m_rot.z);
	m_WorldMatrix *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot.y);
	m_WorldMatrix *= temp;

	temp.setIdentity();
	temp.setRotationX(m_rot.x);
	m_WorldMatrix *= temp;

	//Translate
	temp.setIdentity();
	temp.setTranslation(m_pos);
	m_WorldMatrix *= temp;


	DirectX::XMMATRIX DX_Matrix = DirectX::XMMatrixIdentity();
	// SRT
	DX_Matrix = DX_Matrix *
		DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z) *
		DirectX::XMMatrixRotationZ(m_rot.z) *
		DirectX::XMMatrixRotationY(m_rot.y) *
		DirectX::XMMatrixRotationX(m_rot.x) *
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);


	if (EngineState::GetState() == EngineState::STATE::EDIT)
		m_Owner->SaveState(m_WorldMatrix);
}


const Matrix4x4 Transformation::getWorldMatrix()
{
	return m_WorldMatrix;
}