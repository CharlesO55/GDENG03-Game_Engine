#include "ObjImport.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

#include "Mesh.h"
#include "RotatorScript.h"
#include "ScaleScript.h"
#include "RaycastComponent.h"

ObjImport::ObjImport(const wchar_t* textureFile, const wchar_t* objFile)
{
	m_Components.push_back(new RotatorScript(this));
	//m_Components.push_back(new ScaleScript(this));
	m_Components.push_back(new RaycastComponent(this, RaycastComponent::INTERSECTION_TYPE::SPHERE_CAST));

	m_Tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(textureFile);
	m_Mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(objFile);
}

void ObjImport::initialize()
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// REPLACE ALL THE INDEX AND VERTEX BUFFERS TO MESH
	
	// VERTEX SHADER & BUFFER
	//	Use the shader file for meshes and textures  'VertexShader'
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	//GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	//m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(std::data(m_verts), sizeof(vertexColor), m_verts.size(), shader_byte_code, size_shader, ShaderType::ANIMATED_COLOR);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	// INDEX BUFFER
	//m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(std::data(m_indices), m_indices.size());

	// PIXEL SHADER
	//	Use the shader file for meshes and textures  'PixelShader'
	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	// CONSTANT & CONSTANT BUFFER
	m_cc.m_time = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&m_cc, sizeof(constant));
}

void ObjImport::draw()
{
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_ps, m_Tex);

	// REPLACE BUFFERS WITH MESH BUFFERS
	/*GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);*/


	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_Mesh->getVertexBuffer());
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_Mesh->getIndexBuffer());
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_Mesh->getIndexBuffer()->getSizeIndexList(), 0, 0);

	// Recursive call to draw children
	if (m_child != nullptr) {
		((Primitive*)m_child)->draw();
	}
}