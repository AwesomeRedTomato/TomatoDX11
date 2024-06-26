#pragma once

enum class CB_TYPE
{
	TRANSFORM,
	MATERIAL,
	LIGHT,
	END
};


class ConstantBuffer
{
public:
	void Init(UINT slot, UINT size, UINT count);

	void PushVertexConstant(void* buffer);
	void PushPixelConstant(void* buffer);

protected:
	ComPtr<ID3D11Buffer> _constantBuffer;
	
	BYTE* _buffer = nullptr;
	UINT _slot = 0u;

	UINT _elementSize = 0u;
	UINT _elementCount = 0u;
	UINT _currentIndex = 0u;
};