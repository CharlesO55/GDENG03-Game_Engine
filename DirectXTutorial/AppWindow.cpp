#include "AppWindow.h"

#include "VertexData.h"

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



	vertex triangle_list[] = {
		{-1.f, -1.f, 0.0f,	1,0,0},
		{-0.5f, 0.f, 0.0f,	0,1,0},
		{0.f, -1.f, 0.0f,	0,0,1}
	};

	vertex quad_list[] = {
		// QUAD CAN BE MADE OF 2 TRIANGLES
		{-0.5f, -0.5f, 0.0f,	1,0,0},
		{-0.5f, 0.5f, 0.0f,		0,1,0},
		{0.5f, -0.5f, 0.0f,		0,0,1},
		{0.5f, 0.5f, 0.0f,		1,1,0}
	};

	vertex quad_list1[] = {
		// QUAD CAN BE MADE OF 2 TRIANGLES
		{0.6f, 0.75f, 0.0f,	0,1,0},
		{0.6f, 0.9f, 0.0f,		0,1,0},
		{1.f, 0.75f, 0.0f,		0,1,0},
		{1.f, 0.9f, 0.0f,		0,1,0}
	};

	
	//GraphicsEngine::get()->createShaders();


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	
	
	rb_Rect = (new Primitive(quad_list))->WithShader(shader_byte_code, size_shader, 4);
	gr_Rect = (new Primitive(quad_list1))->WithShader(shader_byte_code, size_shader, 4);
	rb_Tri = (new Primitive(triangle_list))->WithShader(shader_byte_code, size_shader, 3);
	

	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
}

void AppWindow::onUpdate()
{
	//virtual func //Window::onUpdate();

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(
		m_swap_chain, 0.5,0.5f,0.5f,1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right-rc.left, rc.bottom-rc.top);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);


	
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(rb_Rect->getVertexBuffer());
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(rb_Rect->getVertexBuffer()->getSizeVertexList(), 0);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(gr_Rect->getVertexBuffer());
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(gr_Rect->getVertexBuffer()->getSizeVertexList(), 0);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(rb_Tri->getVertexBuffer());
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(rb_Tri->getVertexBuffer()->getSizeVertexList(), 0);

	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	//m_vb->release();
	delete rb_Rect, rb_Tri, gr_Rect;
	
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();

	GraphicsEngine::get()->release();
}
