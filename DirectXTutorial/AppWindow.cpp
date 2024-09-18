#include "AppWindow.h"

struct vec3 {
	float x, y, z;
};
struct vertex {
	vec3 position;
};


AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	//virtual func //Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right-rc.left, rc.bottom-rc.top);



	/*vertex triangle_list[] = {
		{-0.5f, -0.5f, 0.0f},
		{0.0f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f}
	};*/

	vertex quad_list[] = {
		// QUAD CAN BE MADE OF 2 TRIANGLES
		{-0.5f, -0.5f, 0.0f},
		{-0.5f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{0.5f, 0.5f, 0.0f}
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	
	
	//UINT size_list = ARRAYSIZE(triangle_list);
	UINT size_list = ARRAYSIZE(quad_list);

	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	//m_vb->load(triangle_list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	m_vb->load(quad_list, sizeof(vertex), size_list, shader_byte_code, size_shader);
}

void AppWindow::onUpdate()
{
	//virtual func //Window::onUpdate();

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(
		m_swap_chain, 0.5,0.5f,0.5f,1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right-rc.left, rc.bottom-rc.top);
	GraphicsEngine::get()->setShaders();

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	m_vb->release();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}
