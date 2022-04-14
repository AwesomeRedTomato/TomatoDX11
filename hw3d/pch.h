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
//using namespace std;

#include "dxerr.h"
#include <gdiplus.h>
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <dxgidebug.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;
#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib,"gdiplus")

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
	Vertex(XMFLOAT3 p, XMFLOAT2 u) : pos(p), uv(u) {}

	XMFLOAT3 pos;
	XMFLOAT2 uv;
};

struct Transforms
{
	XMMATRIX matWorld;
	XMMATRIX matView;
	XMMATRIX matProjection;
	XMMATRIX matWV;
	XMMATRIX matWVP;
};

extern std::unique_ptr<class Graphics> _gfx;
#define DEVICE _gfx->GetDevice()
#define CONTEXT _gfx->GetContext()
#define CONSTANT_BUFFER(type) _gfx->GetConstantBuffer(type)