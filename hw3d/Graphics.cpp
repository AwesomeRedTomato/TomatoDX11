#include "pch.h"
#include "Graphics.h"
#include "Window.h"
#include "Plane.h"
#include "Cube.h"
#include "Grid.h"
#include "SceneManager.h"

void Graphics::Init(const Window& window)
{	
	_aspectRatio = static_cast<float>(window._width) / static_cast<float>(window._height);



#pragma region InitEngine
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = window._hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	UINT swapCreateFlags = 0u;
#ifndef NDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	THROW_FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&_swapChain,
		&_device,
		nullptr,
		&_context));

	ComPtr<ID3D11Resource> backBuffer;
	THROW_FAILED(_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));
	THROW_FAILED(_device->CreateRenderTargetView(backBuffer.Get(), nullptr, &_rtv));


	// create depth stensil state
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	ComPtr<ID3D11DepthStencilState> pDSState;
	_device->CreateDepthStencilState(&dsDesc, &pDSState);
	_context->OMSetDepthStencilState(pDSState.Get(), 1u);


	ComPtr<ID3D11Texture2D> depthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = 800u;
	descDepth.Height = 600u;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	_device->CreateTexture2D(&descDepth, nullptr, depthStencil.GetAddressOf());

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;
	_device->CreateDepthStencilView(depthStencil.Get(), &descDSV, _dsv.GetAddressOf());

	_context->OMSetRenderTargets(1u, _rtv.GetAddressOf(), _dsv.Get());

	_topology->Init(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_topology->Render();
#pragma endregion
	InitImgui(window);

	Start();

	CreateConstantBuffer((UINT)CB_TYPE::COLOR, sizeof(Tr), 1u);
}

void Graphics::InitImgui(const Window& window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(window._hWnd);
	ImGui_ImplDX11_Init(DEVICE.Get(), CONTEXT.Get());
	ImGui::StyleColorsDark();
}

void Graphics::Start()
{
	GET_SINGLE(SceneManager)->LoadScene();
}

void Graphics::Update()
{
	PushData();

	GET_SINGLE(SceneManager)->Update();
	GET_SINGLE(SceneManager)->UpdateImgui();
}


void Graphics::RenderBegin()
{
	CONTEXT->ClearRenderTargetView(_rtv.Get(), Colors::LightGray);
	CONTEXT->ClearDepthStencilView(_dsv.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::RenderEnd()
{
	_swapChain->Present(0u, 0u);
}

void Graphics::PushData()
{
	static float angle = 0.0f;
	angle += 0.0001;

	Tr tr
	{
		XMMatrixTranspose(
		XMMatrixRotationZ(angle) *
		XMMatrixRotationX(angle) *
		XMMatrixTranslation(0, 0.0f, 0 + 4.0f) *
		XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 10.0f))
	};

	CONSTANT_BUFFER(CB_TYPE::COLOR)->Init(2u, sizeof(Tr), 1u);
	CONSTANT_BUFFER(CB_TYPE::COLOR)->PushData(&tr, sizeof(Tr));
	CONSTANT_BUFFER(CB_TYPE::COLOR)->Render();
}

void Graphics::CreateConstantBuffer(UINT slot, UINT size, UINT count)
{
	std::shared_ptr<ConstantBuffer> buffer = std::make_shared<ConstantBuffer>();
	buffer->Init(slot, size, count);
	_CBs.push_back(buffer);
}
