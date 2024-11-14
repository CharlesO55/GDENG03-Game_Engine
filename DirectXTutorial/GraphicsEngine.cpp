#include "GraphicsEngine.h"
#include "RenderSystem.h"

#include "Debugger.h"

GraphicsEngine* GraphicsEngine::m_engine = nullptr;

GraphicsEngine::GraphicsEngine()
{
	try
	{
		m_render_system = new RenderSystem();
	}
	catch (...) { Debugger::Error("[CREATE ERROR] Graphics Engine>Render System"); }
	try
	{
		m_tex_manager = new TextureManager();
	}
	catch (...) { Debugger::Error("[CREATE ERROR] Graphics Engine>Texture Manager"); }
	try
	{
		m_mesh_manager = new MeshManager();
	}
	catch (...) { Debugger::Error("[CREATE ERROR] Graphics Engine>Mesh Manager"); }


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	m_render_system->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	::memcpy(m_mesh_layout_byte_code, shader_byte_code, size_shader);
	m_mesh_layout_size = size_shader;
	m_render_system->releaseCompiledShader();
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_render_system;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return m_tex_manager;
}

MeshManager* GraphicsEngine::getMeshManager()
{
	return m_mesh_manager;
}

void GraphicsEngine::getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size)
{
	*byte_code = m_mesh_layout_byte_code;
	*size = m_mesh_layout_size;
}

GraphicsEngine::~GraphicsEngine()
{
	GraphicsEngine::m_engine = nullptr;
	delete m_mesh_manager;
	delete m_tex_manager;
	delete m_render_system;

	Debugger::Warning("[Graphics Engine] Destroyed");
}

void GraphicsEngine::create()
{
	if (GraphicsEngine::m_engine) 
		Debugger::Error("[DUPLICATE ERROR] Graphics Engine");
	
	GraphicsEngine::m_engine = new GraphicsEngine();
	Debugger::Success("[Graphics Engine] Created");
}

void GraphicsEngine::release()
{
	if (!GraphicsEngine::m_engine) 
		return;
	delete GraphicsEngine::m_engine;
}

GraphicsEngine* GraphicsEngine::get()
{
	return m_engine;
}