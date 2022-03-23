#pragma once
#include "DxgiInfoManager.h"

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

#ifndef NDEBUG
	DxgiInfoManager _infoManager;
#endif

private:
	HRESULT _hr;
	string _info;
};

#define EXCEPTION() Exception(__LINE__, __FILE__)
#define LAST_EXCEPTION() HrException(__LINE__, __FILE__, GetLastError())

#ifndef NDEBUG
#define THROW_FAILED(hr) if(FAILED((hr))) throw HrException(__LINE__, __FILE__, hr, _infoManager.GetMessages())
#define THROW_INFO(hrcall) _infoManager.Set(); if(FAILED(hr = (hrcall))) THROW_FAILED(hr)
#define NOINFO_THROW_FAILED(hrcall) if(FAILED(hr = (hrcall))) throw HrException(__LINE__, __FILE__, hr)
#else
#define THROW_FAILED(hr) if(FAILED((hr))) throw HrException(__LINE__, __FILE__, hr)
#define NOINFO_THROW_FAILED(hrcall) if(FAILED(hr = (hrcall))) throw HrException(__LINE__, __FILE__, hr)
#endif