#include "pch.h"
#include "Topology.h"
#include "Graphics.h"

void Topology::Init(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	_topology = topology;

	_viewport.Width = 800;
	_viewport.Height = 600;
	_viewport.MinDepth = 0;
	_viewport.MaxDepth = 1;
	_viewport.TopLeftX = 0;
	_viewport.TopLeftY = 0;

}

void Topology::Bind()
{
	CONTEXT->IASetPrimitiveTopology(_topology);
	CONTEXT->RSSetViewports(1u, &_viewport);
}
