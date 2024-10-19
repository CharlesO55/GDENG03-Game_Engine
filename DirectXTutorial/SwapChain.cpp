#include "SwapChain.h"
#include "RenderSystem.h"

#include <iostream>
#include <exception>

SwapChain::SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem* system) : m_system(system)
{
	ID3D11Device* device = m_system->m_d3d_device;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	//Create the swap chain for the window indicated by HWND parameter
	HRESULT hr = m_system->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

	if (FAILED(hr))
	{
		throw std::exception("[CREATE ERROR] SwapChain");
	}

	ID3D11Texture2D* buffer = NULL;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(hr))
	{
		throw std::exception("[CREATE ERROR] SwapChain>TempBuffer");
	}

	hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	buffer->Release();

	if (FAILED(hr))
	{
		throw std::exception("[CREATE ERROR] SwapChain>RenderTargetView");
	}

	D3D11_TEXTURE2D_DESC tex_desc = {};
	tex_desc.Width = width;
	tex_desc.Height = height;
	tex_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tex_desc.Usage = D3D11_USAGE_DEFAULT;
	tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex_desc.MipLevels = 1;
	tex_desc.SampleDesc.Count = 1;
	tex_desc.SampleDesc.Quality = 0;
	tex_desc.MiscFlags = 0;
	tex_desc.ArraySize = 1;
	tex_desc.CPUAccessFlags = 0;

	hr = device->CreateTexture2D(&tex_desc, nullptr, &buffer);
	if (FAILED(hr))
	{
		throw std::exception("[CREATE ERROR] SwapChain>DepthBuffer");
		std::cout << HResultToString(hr);
	}

	hr = device->CreateDepthStencilView(buffer, NULL, &m_dsv);
	buffer->Release();

	if (FAILED(hr))
	{
		throw std::exception("[CREATE ERROR] SwapChain>DepthStencilView");
		std::cout << HResultToString(hr);
	}


	//D3D11_TEXTURE2D_DESC depthStencilDesc;
	//ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	//depthStencilDesc.Width = 1280; // Width of the buffer
	//depthStencilDesc.Height = 720; // Height of the buffer
	//depthStencilDesc.MipLevels = 1;
	//depthStencilDesc.ArraySize = 1;
	//depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // Format of the depth buffer
	//depthStencilDesc.SampleDesc.Count = 1; // Number of multisample anti-aliasing samples
	//depthStencilDesc.SampleDesc.Quality = 0;
	//depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	//depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // Bind flags for depth-stencil
	//depthStencilDesc.CPUAccessFlags = 0; // No CPU access
	////depthStencilDesc.Flag = 0;



	//std::cout << "\nW: " << width;
	//std::cout << "\nH: " << depthStencilDesc.Height;


	//ID3D11Texture2D* depthStencilBuffer;
	//hr = device->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencilBuffer);
	//
	//std::cout << "\nCheck: " << HResultToString(hr);
	//if (FAILED(hr)) {
	//	// Handle error
	//}
	
}




bool SwapChain::present(bool vsync)
{
	m_swap_chain->Present(vsync, NULL);
	return true;
}

std::string SwapChain::HResultToString(HRESULT hr)
{
	// Format the error message
	if (SUCCEEDED(hr))
		return "Success";

	// Convert the HRESULT to a string
	char* errorMsg = nullptr;
	FormatMessageA(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		nullptr,
		hr,
		0, // Default language
		(LPSTR)&errorMsg,
		0,
		nullptr
	);

	std::string result = errorMsg ? errorMsg : "Unknown error";
	LocalFree(errorMsg); // Free the allocated buffer
	return result;
}


SwapChain::~SwapChain()
{
	m_dsv->Release();
	m_rtv->Release();
	m_swap_chain->Release();
}