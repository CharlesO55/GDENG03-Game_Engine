#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4.h"
#include "InputSystem.h"
#include "EngineTime.h"

#include "Cube.h"
#include "Quad.h"
#include "Circle.h"

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();

	// INPUT SYSTEM
	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);

	// GRAPHICS ENGINE
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	m_swap_chain->init(this->m_hwnd, m_windowWidth, m_windowHeight);

	
	// SCENE CAMERA
	m_Camera = new Camera(&m_windowWidth, &m_windowHeight);

	InstantiateShape();

	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}


void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::get()->update();

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0, 0, 1); //BLACK
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(m_windowWidth, m_windowHeight);

	// Update the camera
	m_Camera->update();

	for (int i = 0; i < m_shapes.size(); i++) {
		// Calc the circle's matrices
		m_shapes[i]->updateMatrix(m_Camera->getView(), m_Camera->getProj());

		// Move the cube based on its position on screen space
		m_shapes[i]->update();
		m_shapes[i]->draw();
	}

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	
	
	while (m_shapes.size() > 0) {
		m_shapes.back()->release();
		m_shapes.pop_back();
	}

#if TEST_CUBE
	m_vb->release();
	m_ib->release();
	m_cb->release();
	
	m_vs->release();
	m_ps->release();
#endif 
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::InstantiateShape()
{
	Primitive* newShape = new Circle();
	newShape->initialize();

	m_shapes.push_back(newShape);

	std::cout << "Number of shapes: " << m_shapes.size() << std::endl;
}

void AppWindow::onKeyDown(int key)
{
	switch (key) {
		//ESCAPE
	case 27:
		release();
		break;
		//SPACE
	case 32:
		InstantiateShape();
		break;
		//BACKSPACE
	case 8:
		if (m_shapes.size() > 0) {
			m_shapes.back()->release();
			m_shapes.pop_back();
		}
		break;
		//DELETE
	case 46:
		while (m_shapes.size() > 0) {
			m_shapes.back()->release();
			m_shapes.pop_back();
		}
		break;
	}
}

void AppWindow::onKeyUp(int key)
{
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	InputSystem::get()->setCursorPosition(Point((m_windowWidth / 2), (m_windowHeight / 2)));
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
}