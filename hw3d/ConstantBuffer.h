#pragma once

struct Transform
{
	XMMATRIX _transform;
};

struct Color
{
	struct
	{
		float r;
		float g;
		float b;
		float a;
	} face_colors[6];
};

template<typename T>
class ConstantBuffer
{
public:
	void Init(float angle, int x, int z);
	void Bind();

protected:
	ComPtr<ID3D11Buffer> _constantBuffer;
	ComPtr<ID3D11Buffer> _constantBuffer2;
};