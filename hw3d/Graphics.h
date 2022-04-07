#pragma once
#include "Exception.h"
#include "Mesh.h"
#include "ConstantBuffer.h"
#include "Shader.h"
#include "Topology.h"
#include "Texture.h"
#include "Sampler.h"
#include "Material.h"

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_dx11.h"
#include "Imgui/imgui_impl_win32.h"

class Window;
class Cube;
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

	std::shared_ptr<Mesh> _mesh = std::make_shared<Mesh>();
	std::shared_ptr<Material> _material = std::make_shared<Material>();

	std::shared_ptr<Topology> _topology = std::make_shared<Topology>();
	std::shared_ptr<ConstantBuffer> _cb = std::make_shared<ConstantBuffer>();
};