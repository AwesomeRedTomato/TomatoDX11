#pragma once
class Topology
{
public:
	void Init(D3D11_PRIMITIVE_TOPOLOGY topology);
	void Render();

	D3D11_PRIMITIVE_TOPOLOGY GetTopology() { return _topology; }

protected:
	D3D11_PRIMITIVE_TOPOLOGY _topology;
	D3D11_VIEWPORT _viewport;
};

