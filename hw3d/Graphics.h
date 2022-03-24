#pragma once
#include "Exception.h"

class Graphics
{
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;

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
};