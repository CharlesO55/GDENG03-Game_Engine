#pragma once
#include "Primitive.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexData.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include <vector>

class Cube
{
public:
	Cube();
	~Cube();

	void initialize();
	void updateMatrix(Matrix4 cameraView, Matrix4 cameraProj);
	void draw();

	void scale(Vector3D deltaScale);
	void rotate(Vector3D deltaRot);
	void move(Vector3D deltaPos);

private:
	PixelShader* m_ps = nullptr;
	VertexShader* m_vs = nullptr;

	VertexBuffer* m_vb = nullptr;
	IndexBuffer* m_ib = nullptr;
	ConstantBuffer* m_cb = nullptr;

	std::vector<vertex> m_verts = {};
	std::vector<unsigned int> m_indices = {};

	constant m_cc;

	// Transformations
	Vector3D m_pos, m_rot;
	Vector3D m_scale = Vector3D(1);
};