#pragma once
class TomatoMath
{

	// TODO : °øºÎ mat->float4x4
	// À½.. Matrix(float4x4)
public:
	static XMFLOAT4X4 MatrixScaling(const XMFLOAT3& scale)
	{
		XMFLOAT4X4 matScale;
		XMStoreFloat4x4(&matScale, XMMatrixScaling(scale.x, scale.y, scale.z));

		return matScale;
	}

	static XMFLOAT4X4 MatrixRotationX(float angle)
	{
		XMFLOAT4X4 matRotation;
		XMStoreFloat4x4(&matRotation, XMMatrixRotationX(angle));

		return matRotation;
	}

	static XMFLOAT4X4 MatrixRotationY(float angle)
	{
		XMFLOAT4X4 matRotation;
		XMStoreFloat4x4(&matRotation, XMMatrixRotationY(angle));

		return matRotation;
	}

	static XMFLOAT4X4 MatrixRotationZ(float angle)
	{
		XMFLOAT4X4 matRotation;
		XMStoreFloat4x4(&matRotation, XMMatrixRotationZ(angle));

		return matRotation;
	}

	static XMFLOAT4X4 MatrixRotation(const XMFLOAT3& rotation)
	{
		XMFLOAT4X4 matRotation;

		XMMATRIX M1 = XMMatrixRotationX(rotation.x);
		XMMATRIX M2 = XMMatrixRotationY(rotation.y);
		XMMATRIX M3 = XMMatrixRotationZ(rotation.z);

		XMMATRIX M4 = XMMatrixMultiply(M1, M2);
		XMMatrixMultiply(M4, M3);

		XMStoreFloat4x4(&matRotation, M4);

		return matRotation;
	}

	static XMFLOAT4X4 MatrixTranslation(const XMFLOAT3& position)
	{
		XMFLOAT4X4 matTranslation;
		XMStoreFloat4x4(&matTranslation, XMMatrixTranslation(position.x, position.y, position.z));

		return matTranslation;
	}
};
