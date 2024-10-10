#include "Cube.h"

#include "GraphicsEngine.h"
#include "DeviceContext.h"
Cube::Cube()
{
	//FRONT
	m_verts.push_back({ Vector3D(-0.5f, -0.5f, -0.5f), Vector3D(-0.5f, -0.5f, -0.5f), Vector3D(1, 0, 0), Vector3D(0.2f, 0, 0) });
	m_verts.push_back({ Vector3D(-0.5f,0.5f,-0.5f), Vector3D(-0.5f,0.5f,-0.5f),   Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) });
	m_verts.push_back({ Vector3D(0.5f,0.5f,-0.5f), Vector3D(0.5f,0.5f,-0.5f),  Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) });
	m_verts.push_back({ Vector3D(0.5f,-0.5f,-0.5f), Vector3D(0.5f,-0.5f,-0.5f),    Vector3D(1,0,0), Vector3D(0.2f,0,0) });
	
	//BACK
	m_verts.push_back({ Vector3D(0.5f,-0.5f,0.5f), Vector3D(0.5f,-0.5f,0.5f),   Vector3D(0,1,0), Vector3D(0,0.2f,0) });
	m_verts.push_back({ Vector3D(0.5f,0.5f,0.5f), Vector3D(0.5f,0.5f,0.5f),   Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) });
	m_verts.push_back({ Vector3D(-0.5f,0.5f,0.5f), Vector3D(-0.5f,0.5f,0.5f),  Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) });
	m_verts.push_back({ Vector3D(-0.5f,-0.5f,0.5f), Vector3D(-0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) });
	

	m_indices =
	{
		//FRONT SIDE
		0,1,2,  
		2,3,0,  
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};
}

Cube::~Cube()
{
	m_vb->release();
	m_ib->release();
	m_cb->release();
	m_vs->release();
	m_ps->release();

	m_verts.clear();
}

void Cube::initialize()
{
	m_vb = GraphicsEngine::get()->createVertexBuffer();

	// INDEX BUFFER
	m_ib = GraphicsEngine::get()->createIndexBuffer();
	m_ib->load(std::data(m_indices), m_indices.size());


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;


	// VERTEX SHADER & BUFFER
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(std::data(m_verts), sizeof(vertex), m_verts.size(), shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	// PIXEL SHADER
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	// CONSTANT & CONSTANT BUFFER
	m_cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&m_cc, sizeof(constant));
}

void Cube::updateMatrix(Matrix4 cameraView, Matrix4 cameraProj)
{
	Matrix4 temp;

	m_cc.m_world.setIdentity();
	m_cc.m_world.setScale(m_scale);

	temp.setIdentity();
	temp.setRotationZ(m_rot.z);
	m_cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot.y);
	m_cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_rot.x);
	m_cc.m_world *= temp;

	temp.setIdentity();
	temp.setTranslation(m_pos);
	m_cc.m_world *= temp;
	
	m_cc.m_view = cameraView;
	m_cc.m_proj = cameraProj;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &m_cc);
}

void Cube::draw()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Cube::scale(Vector3D deltaScale)
{
	m_scale = m_scale + deltaScale;
}

void Cube::rotate(Vector3D deltaRot)
{
	m_rot = m_rot + deltaRot;
}

void Cube::move(Vector3D deltaPos)
{
	m_pos = m_pos + deltaPos;
}
