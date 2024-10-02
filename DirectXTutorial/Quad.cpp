#include "Quad.h"

#include "GraphicsEngine.h"


Quad::Quad()
{
	// DEFAULT SHAPE
	this->m_vertexList = new vertex[4];
	m_vertexList[0] = { Vector3D(-0.5f, -0.5f, 0.0f), Vector3D(0, 0, 0), Vector3D(0, 1, 0) }; // POS1
	m_vertexList[1] = { Vector3D(-0.5f,0.5f,0.0f),     Vector3D(1,1,0), Vector3D(0,1,1) }; // POS2
	m_vertexList[2] = { Vector3D(0.5f,-0.5f,0.0f),    Vector3D(0,0,1),  Vector3D(1,0,0) }; // POS2
	m_vertexList[3] = { Vector3D(0.5f,0.5f,0.0f),     Vector3D(1,1,1), Vector3D(0,0,1) };
}

Quad::Quad(Quad& copy, RECT rc)
{
	m_vertexList = new vertex(*copy.m_vertexList);
	m_vb = new VertexBuffer(*copy.m_vb);

	createConstantBuffer(rc);
}

Quad::~Quad()
{
	Primitive::~Primitive();
}

void Quad::createVertexBuffer(void* shader_byte_code, UINT size_byte_shader)
{
	Primitive::createVertexBuffer(shader_byte_code, size_byte_shader, 4);
}