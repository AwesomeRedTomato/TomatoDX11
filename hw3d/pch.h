#pragma once

#include <Windows.h>
#include <stdlib.h>
#include <tchar.h>
#include <chrono>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <optional>
#include <queue>
#include <sstream>
#include <iomanip>
#include <exception>
#include <bitset>
#include <memory>
#include <assert.h>
#include <cmath>
#include <algorithm>
#include <float.h>

#include <gdiplus.h>
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <dxgidebug.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include "SimpleMath.h"
#include "dxerr.h"
using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;
#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib,"gdiplus")


using MATRIX = SimpleMath::Matrix;
using FLOAT2 = SimpleMath::Vector2;
using FLOAT3 = SimpleMath::Vector3;
using FLOAT4 = SimpleMath::Vector4;

#define SINGLETON(type)				\
private:							\
	type() {}						\
	~type() {}						\
public:								\
	static type* GetInstance()		\
	{								\
		static type instance;		\
		return &instance;			\
	}								\

#define GET_SINGLE(type)	type::GetInstance()

struct Vertex
{
	Vertex() {}
	Vertex(FLOAT3 p, FLOAT2 u, FLOAT3 n, FLOAT3 t) : pos(p), uv(u), normal(n), tangent(t) {}

	FLOAT3 pos;
	FLOAT2 uv;
	FLOAT3 normal;
	FLOAT3 tangent;
};

struct TRANSFORM_PARAMS
{
	MATRIX matWorld;
	MATRIX matView;
	MATRIX matProjection;
	MATRIX matWV;
	MATRIX matWVP;
};

extern std::unique_ptr<class Graphics> _gfx;
#define DEVICE _gfx->GetDevice()
#define CONTEXT _gfx->GetContext()
#define CONSTANT_BUFFER(type) _gfx->GetConstantBuffer(type)