#pragma once

enum class CB_TYPE : UINT
{
	TRANSFORM,
	COLOR,
	LIGHT,
	END,
};

//struct Transform
//{
//	XMMATRIX _transform;
//};
//
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

class ConstantBuffer
{
public:
	void Init(void* buffer, UINT size);
	void Bind();

protected:
	ComPtr<ID3D11Buffer> _constantBuffer;
	
	BYTE* _buffer = nullptr;

	UINT _elementSize = 0u;
	UINT _elementCount = 0u;
};