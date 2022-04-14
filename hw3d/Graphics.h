#pragma once
#include "Exception.h"
#include "Mesh.h"
#include "ConstantBuffer.h"
#include "Shader.h"
#include "Topology.h"
#include "Texture.h"
#include "Sampler.h"
#include "Material.h"
#include "Transform.h"

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_win32.h"
#include "Imgui/imgui_impl_dx11.h"

struct Tr
{
	XMMATRIX tf;
};

class Window;
class Cube;
class Graphics
{
public:
	void Init(const Window& window);

public:
	ComPtr<ID3D11Device> GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext> GetContext() { return _context; }
	std::shared_ptr<ConstantBuffer> GetConstantBuffer(CB_TYPE type) { return _CBs[static_cast<UINT>(CB_TYPE::TRANSFORM)]; }

public:
	void RenderBegin();
	void RenderEnd();

	void DrawTriangle(float angle, float x, float z);
	void CreateConstantBuffer(UINT slot, UINT size, UINT count);

#ifndef NDEBUG
	DxgiInfoManager _infoManager;
#endif

public:
	float _aspectRatio = 0;

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<IDXGISwapChain> _swapChain;
	ComPtr<ID3D11DeviceContext> _context;

	ComPtr<ID3D11RenderTargetView> _rtv;
	ComPtr<ID3D11DepthStencilView> _dsv;

	std::shared_ptr<Mesh> _mesh = std::make_shared<Mesh>();
	std::shared_ptr<Material> _material = std::make_shared<Material>();
	std::shared_ptr<Topology> _topology = std::make_shared<Topology>();

	std::vector<std::shared_ptr<ConstantBuffer>> _CBs;
};