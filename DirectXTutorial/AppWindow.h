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

#include "Quad.h"

#include <vector>

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

private:
	void createObjects(void* shader_byte_code, size_t size_shader, RECT rc);
	void updateQuadPosition();
	Quad* createNewSquare(Quad* original);

private:
	SwapChain* m_swap_chain;
	VertexShader* m_vs;
	PixelShader* m_ps;

	std::vector<Primitive*> m_objects;
	
	ConstantBuffer* m_cb;

	Quad* createParentAndChild(void* shader_byte_code, size_t size_shader, RECT rc);

	void* v_shader_byte_code = nullptr;
	size_t v_size_shader = 0;


	long m_old_delta;
	long m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	float ticks = 0;
};