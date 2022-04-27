#define FULL_WINTARD
#define _HAS_STD_BYTE 0

#include "pch.h"
#include "Texture.h"
#include "Exception.h"
#include "Graphics.h"

namespace Gdiplus
{
	using std::min;
	using std::max;
}

void Texture::Init()
{
	D3D11_TEXTURE2D_DESC tex2DDesc = {};
	tex2DDesc.Width = _width;
	tex2DDesc.Height = _height;
	tex2DDesc.MipLevels = 1;
	tex2DDesc.ArraySize = 1;
	tex2DDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	tex2DDesc.SampleDesc.Count = 1;
	tex2DDesc.SampleDesc.Quality = 0;
	tex2DDesc.Usage = D3D11_USAGE_DEFAULT;
	tex2DDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	tex2DDesc.CPUAccessFlags = 0;
	tex2DDesc.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = _buffer.get();
	sd.SysMemPitch = _width * sizeof(Texture::Color);
	DEVICE->CreateTexture2D(&tex2DDesc, &sd, _tex2D.GetAddressOf());

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = tex2DDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;
	DEVICE->CreateShaderResourceView(_tex2D.Get(), &srvDesc, _srv.GetAddressOf());
}

void Texture::Render()
{
	CONTEXT->PSSetShaderResources(0u, 1u, _srv.GetAddressOf());
}

void Texture::Load(const std::wstring& path)
{
	if (!_buffer)
	{
		Gdiplus::Bitmap bitmap(path.c_str());
		if (bitmap.GetLastStatus() != Gdiplus::Status::Ok)
		{
			MessageBox(nullptr, "Load Image Failed", "Failed", MB_OK);
		}

		_width = bitmap.GetWidth();
		_height = bitmap.GetHeight();
		_buffer = std::make_unique<Color[]>(_width * _height);

		for (UINT y = 0; y < _height; ++y)
		{
			for (UINT x = 0; x < _width; ++x)
			{
				Gdiplus::Color c;
				bitmap.GetPixel(x, y, &c);
				_buffer[y * _width + x] = c.GetValue();
			}
		}
	}
}

void Texture::Save(const std::string& filename)
{
	auto GetEncoderClsid = [&filename](const WCHAR* format, CLSID* pClsid) -> void
	{
		UINT num = 0;
		UINT size = 0;


		Gdiplus::ImageCodecInfo* imageCodecInfo = nullptr;

		Gdiplus::GetImageEncodersSize(&num, &size);
		assert(size == 0);

		imageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
		assert(imageCodecInfo == nullptr);

		Gdiplus::GetImageEncoders(num, size, imageCodecInfo);

		for (UINT i = 0; i < num; i++)
		{
			if (wcscmp(imageCodecInfo[i].MimeType, format) == 0)
			{
				*pClsid = imageCodecInfo[i].Clsid;
				free(imageCodecInfo);
				return;
			}
		}

		free(imageCodecInfo);
	};

	CLSID bmpID;
	GetEncoderClsid(L"image/bmp", &bmpID);

	WCHAR wideName[512];
	mbstowcs_s(nullptr, wideName, filename.c_str(), _TRUNCATE);

	Gdiplus::Bitmap bitmap(_width, _height, _width * sizeof(Color), PixelFormat64bppARGB, (BYTE*)_buffer.get());
	if (bitmap.Save(wideName, &bmpID, nullptr) != Gdiplus::Status::Ok) 
	{
		MessageBox(nullptr, "Save Image Failed", "Failed", MB_OK);
	}
}

void Texture::Copy(const Texture& src)
{
	memcpy(_buffer.get(), src._buffer.get(), _width * _height * sizeof(Color));
}
