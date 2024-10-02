#include "Primitive.h"

#include "GraphicsEngine.h"
#include "DeviceContext.h"

Primitive::Primitive(vertex* vertices) : m_vertexList(vertices)
{
}

Primitive::~Primitive()
{
	m_vb->release();
}

Primitive* Primitive::WithShader(void* shader_byte_code, UINT size_byte_shader, UINT vertex_count)
{
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	m_vb->load(this->m_vertexList, sizeof(vertex), vertex_count, shader_byte_code, size_byte_shader);


	return this;
}

VertexBuffer* Primitive::getVertexBuffer() const
{
	return m_vb;
}

void Primitive::draw()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->getVertexBuffer());
	
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(this->getVertexBuffer()->getSizeVertexList(), 0);
}