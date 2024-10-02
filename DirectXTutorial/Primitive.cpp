#include "Primitive.h"

#include "GraphicsEngine.h"
#include "DeviceContext.h"

Primitive::Primitive() {}

Primitive::Primitive(vertex* vertices) : m_vertexList(vertices)
{
}


Primitive::~Primitive()
{
	m_vb->release();
	m_cb->release();
	delete[] m_vertexList;
	std::cout << "\nPrimitive destroyed";
}

void Primitive::createVertexBuffer(void* shader_byte_code, UINT size_byte_shader, UINT vertex_count)
{
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	m_vb->load(this->m_vertexList, sizeof(vertex), vertex_count, shader_byte_code, size_byte_shader);
}

void Primitive::createConstantBuffer(RECT rc)
{
	m_cc.m_time = 0;
	m_cc.m_world.setIdentity();
	m_cc.m_view.setIdentity();
	m_cc.m_proj.setOrthoLH
	(
		(rc.right - rc.left) / 400.0f,
		(rc.bottom - rc.top) / 400.0f,
		-4.0f,
		4.0f
	);

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&m_cc, sizeof(constant));
}

void Primitive::transform(Vector3D translate, Vector3D scale, Vector3D rotate)
{
	// SCALE
	m_cc.m_world.setIdentity();
	m_cc.m_world.setScale(scale);

	// ROTATE
	Matrix4 transformations;
	transformations.setIdentity();
	transformations.setRotationZ(rotate.z);
	m_cc.m_world *= transformations;

	transformations.setIdentity();
	transformations.setRotationY(rotate.y);
	m_cc.m_world *= transformations;

	transformations.setIdentity();
	transformations.setRotationX(rotate.x);
	m_cc.m_world *= transformations;

	// TRANSLATE
	transformations.setIdentity();
	transformations.setTranslation(translate);
	m_cc.m_world *= transformations;

	

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &m_cc);
}


void Primitive::draw(VertexShader* vs, PixelShader* ps)
{
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(ps, m_cb);


	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->m_vb);
	
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(this->m_vb->getSizeVertexList(), 0);
}