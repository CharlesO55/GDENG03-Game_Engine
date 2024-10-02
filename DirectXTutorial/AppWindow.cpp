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


	// ALTER THE VERTEX struct and VERTEXBUFFER AS WELL IF CONTENTS CHANGE
	vertex triangle_list[] = {
		{Vector3D(- 1.f, -1.f, 0.0f),	Vector3D(1,0,0),	Vector3D(1,0,0)},
		{Vector3D(-0.5f, 0.f, 0.0f),	Vector3D(0,1,0),	Vector3D(0,1,0)},
		{Vector3D(0.f, -1.f, 0.0f),		Vector3D(0,0,1),	Vector3D(0,0,1)}
	};

	vertex quad_list[] = {
		{Vector3D(-0.5f,-0.5f,0.0f),    Vector3D(0,0,0), Vector3D(0,1,0) }, // POS1
		{Vector3D(-0.5f,0.5f,0.0f),     Vector3D(1,1,0), Vector3D(0,1,1) }, // POS2
		{ Vector3D(0.5f,-0.5f,0.0f),    Vector3D(0,0,1),  Vector3D(1,0,0) },// POS2
		{ Vector3D(0.5f,0.5f,0.0f),     Vector3D(1,1,1), Vector3D(0,0,1) }
	};


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	
	
	rb_Rect = (new Primitive(quad_list))->WithShader(shader_byte_code, size_shader, 4);
	rb_Tri = (new Primitive(triangle_list))->WithShader(shader_byte_code, size_shader, 3);
	

	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();


	// CONSTANT BUFFER
	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void AppWindow::onUpdate()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(
		m_swap_chain, 0.5,0.5f,0.5f,1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right-rc.left, rc.bottom-rc.top);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);


	updateQuadPosition();

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	rb_Rect->draw();
	rb_Tri->draw();

	m_swap_chain->present(false);

	// UPDATE TIME
	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount64();
	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	//m_vb->release();
	delete rb_Rect, rb_Tri;
	
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();

	GraphicsEngine::get()->release();
}

void AppWindow::updateQuadPosition()
{
	constant cc;
	cc.m_time = ::GetTickCount64();

	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;


	Matrix4 temp;

	m_delta_scale += m_delta_time / 0.15f;

	cc.m_world.setIdentity();
	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));

	temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_delta_pos));

	cc.m_world *= temp;


	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 400.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 400.0f,
		-4.0f,
		4.0f
	);

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}