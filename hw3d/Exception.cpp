#include "pch.h"
#include "Exception.h"

Exception::Exception(int line, const char* file) noexcept
	:
	_line(line), _file(file)
{
}

const char* Exception::what() const noexcept
{
	ostringstream oss;
	oss << "Exception" << endl << GetOriginString();
	
	return oss.str().c_str();
}

string Exception::GetOriginString() const noexcept
{
	ostringstream oss;
	oss << "[File] " << _file << "[Line] " << _line << endl;

	return oss.str();
}

HrException::HrException(int line, const char* file, HRESULT hr) noexcept
	:
	Exception(line, file), _hr(hr)
{
}

const char* HrException::what() const noexcept
{
	ostringstream oss;
	oss << "HrException" << endl << "[ErrorCode] " << _hr << endl <<
		"[Description] " << TranslateErrorCode(_hr) << endl;

	return oss.str().c_str();
}

string HrException::TranslateErrorCode(HRESULT hr) const noexcept
{
	char* msgBuffer = nullptr;

	DWORD msgLength = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&msgBuffer),
		0,
		nullptr);

	string errorString = msgBuffer;
	LocalFree(msgBuffer);

	return errorString;
}