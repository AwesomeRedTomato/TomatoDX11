#pragma once
class Shader
{
public:
	void Init();
	void Bind();

	void CreateVertexShader(const wstring& path);
	void CreatePixelShader(const wstring& path);

	void CreateShader(const wstring& path, ComPtr<ID3DBlob>& pBlob);

	ComPtr<ID3DBlob> GetByteCode();

protected:
	ComPtr<ID3DBlob> _vsBlob;
	ComPtr<ID3DBlob> _psBlob;

	ComPtr<ID3D11VertexShader> _vertexShader;
	ComPtr<ID3D11PixelShader> _pixelShader;

	ComPtr<ID3D11InputLayout> _inputLayout;
};
