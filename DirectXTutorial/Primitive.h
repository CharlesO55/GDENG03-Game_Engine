#pragma once
#include "VertexData.h"
#include "VertexBuffer.h"


class Primitive
{
private:
	VertexBuffer* m_vb = nullptr;
	vertex* m_vertexList = nullptr;

public:
	// BUILDER
	Primitive(vertex* vertices);
	Primitive* WithShader(void* shader_byte_code, UINT size_byte_shader, UINT vertex_count);

	~Primitive();



	// GETTERS
	VertexBuffer* getVertexBuffer() const;
};