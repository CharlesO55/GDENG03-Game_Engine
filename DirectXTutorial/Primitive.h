#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexData.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include <vector>

#include "SceneObject.h"

class Primitive : public SceneObject
{
public:
	Primitive();
	~Primitive();

	void initialize();
	virtual void update() {};

	void updateMatrix(Matrix4x4 cameraView, Matrix4x4 cameraProj, Matrix4x4* worldOverride = nullptr);
	void draw();
	void release();


	void scale(Vector3D deltaScale);
	void rotate(Vector3D deltaRot);
	void move(Vector3D deltaPos);

protected:
	PixelShaderPtr m_ps = nullptr;
	VertexShaderPtr m_vs = nullptr;
	VertexBufferPtr m_vb = nullptr;
	IndexBufferPtr m_ib = nullptr;
	ConstantBufferPtr m_cb = nullptr;

	std::vector<vertexColor> m_verts = {};
	std::vector<unsigned int> m_indices = {};

	TexturePtr m_tex = nullptr;
	

	constant m_cc;

	// Transformations
	Vector3D m_pos = Vector3D(0);
	Vector3D m_rot = Vector3D(0);
	Vector3D m_scale = Vector3D(1);
};