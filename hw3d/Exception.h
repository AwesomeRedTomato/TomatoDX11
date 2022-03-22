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

class HrException : public Exception
{
public:
	HrException(int line, const char* file, HRESULT hr)	noexcept;

	const char* what() const noexcept override;
	string TranslateErrorCode(HRESULT hr) const noexcept;
private:
	HRESULT _hr;
};

#define EXCEPTION() Exception(__LINE__, __FILE__)
#define HREXCEPTION(hr) HrException(__LINE__, __FILE__, GetLastError())