#include "Primitive.h"

#include "GraphicsEngine.h"
#include "DeviceContext.h"

Primitive::Primitive() {
	m_transform.setIdentity();
}

Primitive::Primitive(vertex* vertices) : m_vertexList(vertices)
{
	m_transform.setIdentity();
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

void Primitive::addChild(Primitive* child, bool keepTransform)
{
	this->m_child = child;
	this->m_keepTransform = keepTransform;
}

void Primitive::transform(Vector3D translate, Vector3D scale, Vector3D rotate)
{
	// SCALE
	m_transform.setIdentity();
	m_transform.setScale(scale);

	
	// ROTATE
	Matrix4 transformations;
	transformations.setIdentity();
	transformations.setRotationZ(rotate.z);
	m_transform *= transformations;

	transformations.setIdentity();
	transformations.setRotationY(rotate.y);
	m_transform *= transformations;


	transformations.setIdentity();
	transformations.setRotationX(rotate.x);
	m_transform *= transformations;

	// TRANSLATE
	transformations.setIdentity();
	transformations.setTranslation(translate);
	m_transform *= transformations;

	m_cc.m_world = m_transform;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &m_cc);
}

Primitive* Primitive::getChild()
{
	return this->m_child;
}


void Primitive::update(double deltaTime)
{
	if (updateDir == 1 && updateSpeed > 10) {
		updateDir = -1;
	}
	else if (updateDir == -1 && updateSpeed < 0) {
		updateDir = 1;
	}
	updateSpeed += updateDir * deltaTime;

	totalTime += deltaTime * updateSpeed * updateDir;

	m_cc.m_time = (sin(totalTime) + 1) / 2;
	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &m_cc);
}

void Primitive::draw(VertexShader* vs, PixelShader* ps, constant* global_cc)
{
	if (global_cc != nullptr && !m_keepTransform) {
		m_cc.m_world = m_transform;
		m_cc.m_world *= global_cc->m_world;

		
		m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &m_cc);
	}


	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(ps, m_cb);


	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->m_vb);
	
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(this->m_vb->getSizeVertexList(), 0);
}

void Primitive::drawChildren(VertexShader* vs, PixelShader* ps)
{
	if (m_child == nullptr) {
		return;
	}

	m_child->draw(vs, ps, &m_cc);

	if (m_child->m_child != nullptr)
		m_child->drawChildren(vs, ps);
}