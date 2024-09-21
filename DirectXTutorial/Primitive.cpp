#include "Primitive.h"

#include "GraphicsEngine.h"


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