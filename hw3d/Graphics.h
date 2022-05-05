#pragma once
#include "Exception.h"
#include "ConstantBuffer.h"
#include "Topology.h"
#include "Transform.h"
#include "Shader.h"
#include "Texture.h"	
#include "Mesh.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"

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




public:
	void DrawTriangle(float angle, float x, float z);
	void CreateConstantBuffer(UINT slot, UINT size, UINT count);

	void SetCamera(XMMATRIX camera) { _camera = camera; }
	XMMATRIX GetCamera() { return _camera; }

private:
	XMMATRIX _projection;
	XMMATRIX _camera;


	Transforms _transform;



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

	std::shared_ptr<Topology> _topology = std::make_shared<Topology>();
	std::vector<std::shared_ptr<ConstantBuffer>> _CBs;

	std::shared_ptr<Texture> texture = std::make_shared<Texture>();

	std::shared_ptr<GameObject> _gameObject = std::make_shared<GameObject>();

};