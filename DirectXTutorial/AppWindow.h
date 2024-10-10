#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Primitive.h"
#include "ConstantBuffer.h"

#include "InputListener.h"

#include "Camera.h"
#include "Cube.h"

#include <vector>

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

private:
	void createObjects();
	void update();
	void updateQuadPosition();

private:
	SwapChain* m_swap_chain;
	
	std::vector<Primitive*> m_objects;
	

	//Quad* createParentAndChild(void* shader_byte_code, size_t size_shader, RECT rc);

	void* v_shader_byte_code = nullptr;
	size_t v_size_shader = 0;

private:
	long m_old_delta;
	long m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	float ticks = 0;

private:
	// TESTING
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	ConstantBuffer* m_cb;
	VertexShader* m_vs;
	PixelShader* m_ps;

	Primitive* testTriangle;
	//Quad* testQuad;

	Camera* m_Camera;

	Cube* m_testCube;

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& mouse_pos) override;
	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

	virtual void onFocus() override;
	virtual void onKillFocus() override;

	float scaleCube = 1;
	float rotX = 0;
	float rotY = 0;
};