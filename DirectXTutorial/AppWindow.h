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

class Primitive;

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
	SwapChain* m_swap_chain;
	Camera* m_Camera = nullptr;
	std::vector<Primitive*> m_shapes = {};

	// TESTING
	VertexBuffer* m_vb = nullptr;
	IndexBuffer* m_ib = nullptr;
	ConstantBuffer* m_cb = nullptr;
	VertexShader* m_vs = nullptr;
	PixelShader* m_ps = nullptr;


private:
	void InstantiateShape();

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
};