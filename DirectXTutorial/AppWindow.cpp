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


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	
	
	createObjects(shader_byte_code, size_shader, rc);

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

void AppWindow::createObjects(void* shader_byte_code, size_t size_shader, RECT rc) {
	// ALTER THE VERTEX struct and VERTEXBUFFER AS WELL IF CONTENTS CHANGE
	vertex triangle_list[] = {
		{Vector3D(-1.f, -1.f, 0.0f),	Vector3D(1,0,0),	Vector3D(1,0,0)},
		{Vector3D(-0.5f, 0.f, 0.0f),	Vector3D(0,1,0),	Vector3D(0,1,0)},
		{Vector3D(0.f, -1.f, 0.0f),		Vector3D(0,0,1),	Vector3D(0,0,1)}
	};
	

	Primitive* rb_Tri = new Primitive(triangle_list);
	rb_Tri->createVertexBuffer(shader_byte_code, size_shader, 3);
	rb_Tri->createConstantBuffer(rc);
	m_objects.push_back(rb_Tri);

	// [1] SQUARE
	Quad* square = new Quad();
	square->createVertexBuffer(shader_byte_code, size_shader);
	square->createConstantBuffer(rc);
	square->transform(Vector3D(0, 0, 0), Vector3D(0.5, 0.5, 1), Vector3D(0, 0, 0));
	m_objects.push_back(square);
	
	// [2] TALL RECT AT RIGHT
	// COPIES ONLY THE VERTEX BUFFER. NEW CONSTANT BUFFER IS CREATED
	Quad* tall_rect = new Quad(*square, rc);
	tall_rect->transform(Vector3D(1, 0, 0), Vector3D(0.1, 1.3, 1), Vector3D(0, 0, 0));
	m_objects.push_back(tall_rect);

	// [3] TILTED RECT AT UPPER LEFT
	Quad* tilt_rect = new Quad(*square, rc);
	tilt_rect->transform(Vector3D(-0.8, 0.4, 0), Vector3D(0.5, 1, 1), Vector3D(0, 0, 40));
	m_objects.push_back(tilt_rect);
}

void AppWindow::onUpdate()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(
		m_swap_chain, 0.5,0.5f,0.5f,1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right-rc.left, rc.bottom-rc.top);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);


	//updateQuadPosition();


	for (int i = 0; i < m_objects.size(); i++) {
		this->m_objects[i]->draw(m_vs, m_ps);
	}

	m_swap_chain->present(false);

	// UPDATE TIME
	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount64();
	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	m_objects.clear();
	m_objects.shrink_to_fit();

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
	cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));

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