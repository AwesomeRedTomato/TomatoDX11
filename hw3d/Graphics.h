#pragma once
#include "Exception.h"
#include "Mesh.h"

class Window;
class Graphics
{
public:
	void Init(const Window& window);

public:
	ComPtr<ID3D11Device> GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext> GetContext() { return _context; }

public:
	void RenderBegin();
	void RenderEnd();


	void DrawTriangle(float angle, float x, float z);



#ifndef NDEBUG
	DxgiInfoManager _infoManager;
#endif

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<IDXGISwapChain> _swapChain;
	ComPtr<ID3D11DeviceContext> _context;

	ComPtr<ID3D11RenderTargetView> _rtv;
	ComPtr<ID3D11DepthStencilView> _dsv;

	shared_ptr<Mesh> _mesh = make_unique<Mesh>();
};