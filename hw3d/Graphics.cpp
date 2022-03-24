#include "pch.h"
#include "Graphics.h"
#include "Window.h"

void Graphics::Init(const Window& window)
{	
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

	_context->OMSetRenderTargets(1u, _rtv.GetAddressOf(),_dsv.Get());

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

void Graphics::DrawTriangle(float angle, float x, float z)
{
	vector<Vertex> vertices(8);

	vertices[0] = Vertex(XMFLOAT3(-1.0f, -1.0f, -1.0f));
	vertices[1] = Vertex(XMFLOAT3(1.0f,-1.0f,-1.0f));
	vertices[2] = Vertex(XMFLOAT3(-1.0f,1.0f,-1.0f));
	vertices[3] = Vertex(XMFLOAT3(1.0f,1.0f,-1.0f));
	vertices[4] = Vertex(XMFLOAT3(-1.0f,-1.0f,1.0f));
	vertices[5] = Vertex(XMFLOAT3(1.0f,-1.0f,1.0f));
	vertices[6] = Vertex(XMFLOAT3(-1.0f,1.0f,1.0f));
	vertices[7] = Vertex(XMFLOAT3(1.0f, 1.0f, 1.0f));

	vector<uint16_t> idx(36);

	// ¾Õ¸é
	idx[0] = 0; idx[1] = 2; idx[2] = 1;
	idx[3] = 2; idx[4] = 3; idx[5] = 1;
	// µÞ¸é
	idx[6] = 1; idx[7] = 3; idx[8] = 5;
	idx[9] = 3; idx[10] = 7; idx[11] = 5;
	// À­¸é
	idx[12] = 2; idx[13] = 6; idx[14] = 3;
	idx[15] = 3; idx[16] = 6; idx[17] = 7;
	// ¾Æ·§¸é
	idx[18] = 4; idx[19] = 5; idx[20] = 7;
	idx[21] = 4; idx[22] = 7; idx[23] = 6;
	// ¿ÞÂÊ¸é
	idx[24] = 0; idx[25] = 4; idx[26] = 2;
	idx[27] = 2; idx[28] = 4; idx[29] = 6;
	// ¿À¸¥ÂÊ¸é
	idx[30] = 0; idx[31] = 1; idx[32] = 4;
	idx[33] = 1; idx[34] = 5; idx[35] = 4;

	_mesh->Init(vertices, idx);
	_mesh->Bind();

	// create constant buffer for transform matrix
	struct ConstantBuffer
	{
		XMMATRIX transform;
	};
	const ConstantBuffer cb =
	{
		{
			 XMMatrixTranspose(
					XMMatrixRotationZ(angle)*
					XMMatrixRotationX(angle)*
					XMMatrixTranslation(x,0.0f,z + 4.0f)*
					XMMatrixPerspectiveLH(1.0f,3.0f / 4.0f,0.5f,10.0f))
		}
	};

	ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;
	_device->CreateBuffer(&cbd, &csd, &pConstantBuffer);

	_context->VSSetConstantBuffers(0, 1, pConstantBuffer.GetAddressOf());

	
	struct ConstantBuffer2
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} face_colors[6];
	};
	
	const ConstantBuffer2 cb2 =
	{
		{
			{1.0f,0.0f,1.0f},
			{1.0f,0.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,0.0f,1.0f},
			{1.0f,1.0f,0.0f},
			{0.0f,1.0f,1.0f},
		}
	};

	ComPtr<ID3D11Buffer> pConstantBuffer2;
	D3D11_BUFFER_DESC cbd2;
	cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd2.Usage = D3D11_USAGE_DEFAULT;
	cbd2.CPUAccessFlags = 0u;
	cbd2.MiscFlags = 0u;
	cbd2.ByteWidth = sizeof(cb2);
	cbd2.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd2 = {};
	csd2.pSysMem = &cb2;
	_device->CreateBuffer(&cbd2, &csd2, &pConstantBuffer2);

	// bind constant buffer to pixel shader
	_context->PSSetConstantBuffers(0u, 1u, pConstantBuffer2.GetAddressOf());


	// create pixel shader
	ComPtr<ID3D11PixelShader> pPixelShader;
	ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	_device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);

	// bind pixel shader
	_context->PSSetShader(pPixelShader.Get(), nullptr, 0u);


	// create vertex shader
	ComPtr<ID3D11VertexShader> pVertexShader;
	D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	_device->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

	// bind vertex shader
	_context->VSSetShader(pVertexShader.Get(), nullptr, 0u);


	// input (vertex) layout (2d position only)
	ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	_device->CreateInputLayout(
		ied, (UINT)std::size(ied),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayout);

	// bind vertex layout
	_context->IASetInputLayout(pInputLayout.Get());


	// Set primitive topology to triangle list (groups of 3 vertices)
	_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// configure viewport
	D3D11_VIEWPORT vp;
	vp.Width = 800;
	vp.Height = 600;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	_context->RSSetViewports(1u, &vp);


	_context->DrawIndexed((UINT)std::size(idx), 0u, 0u);
}
