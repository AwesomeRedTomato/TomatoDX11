#pragma once

class Exception : public exception
{
public:
	Exception(int line, const char* file) noexcept;

	const char* what() const noexcept override;
	string GetOriginString() const noexcept;
private:
	int _line;
	string _file;
};

class WinException : public Exception
{
public:
	WinException(int line, const char* file, HRESULT hr)	noexcept;

	const char* what() const noexcept override;
	string TranslateErrorCode(HRESULT hr) const noexcept;
private:
	HRESULT _hr;
};

class HrException : public Exception
{
public:
	HrException(int line, const char* file, HRESULT hr, vector<string> infoMsgs = {}) noexcept;
	
	const char* what() const noexcept override;
	const char* GetType() const noexcept;
	
	HRESULT GetErrorCode() const noexcept;
	string GetErrorString() const noexcept;
	string GetErrorDescription() const noexcept;
	string GetErrorInfo() const noexcept;

private:
	HRESULT _hr;
	string _info;
};

#define GFX_THROW_FAILED(hr) if(FAILED((hr))) throw HrException(__LINE__, __FILE__, hr)