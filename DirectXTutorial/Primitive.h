#pragma once
#include "VertexData.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"

class VertexShader;
class PixelShader;

class Primitive
{
protected:
	vertex* m_vertexList;
	VertexBuffer* m_vb = nullptr;

	constant m_cc;
	ConstantBuffer* m_cb = nullptr;

public:
	Primitive();
	Primitive(vertex* vertices);
	void createVertexBuffer(void* shader_byte_code, UINT size_byte_shader, UINT vertex_count);
	void createConstantBuffer(RECT rc);
	~Primitive();

	void transform(Vector3D translate, Vector3D scale, Vector3D rotate);

public:
	void draw(VertexShader* vs, PixelShader* ps);
};