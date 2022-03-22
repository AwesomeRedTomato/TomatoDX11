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

WinException::WinException(int line, const char* file, HRESULT hr) noexcept
	:
	Exception(line, file), _hr(hr)
{
}

const char* WinException::what() const noexcept
{
	ostringstream oss;
	oss << "HrException" << endl << "[ErrorCode] " << _hr << endl <<
		"[Description] " << TranslateErrorCode(_hr) << endl;

	return oss.str().c_str();
}

string WinException::TranslateErrorCode(HRESULT hr) const noexcept
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

HrException::HrException(int line, const char* file, HRESULT hr, vector<string> infoMsgs) noexcept
	: Exception(line,file), _hr(hr)
{
	for (const auto& m : infoMsgs)
	{
		_info += m;
		_info.push_back('\n');
	}
	if (!_info.empty())
	{
		_info.pop_back();
	}
}

const char* HrException::what() const noexcept
{
	ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << hex << uppercase << GetErrorCode()
		<< dec << " (" << (unsigned long)GetErrorCode() << ")" << endl
		<< "[Error String] " << GetErrorString() << endl
		<< "[Description] " << GetErrorDescription() << endl;
	if (!_info.empty())
	{
		oss << "\n[Error Info]\n" << GetErrorInfo() << endl << endl;
	}
	oss << GetOriginString();

	return oss.str().c_str();
}

const char* HrException::GetType() const noexcept
{
	return "HrException";
}

HRESULT HrException::GetErrorCode() const noexcept
{
	return _hr;
}

string HrException::GetErrorString() const noexcept
{
	return DXGetErrorString(_hr);
}

string HrException::GetErrorDescription() const noexcept
{
	char buffer[512];
	DXGetErrorDescription(_hr, buffer, sizeof(buffer));
	return buffer;
}

string HrException::GetErrorInfo() const noexcept
{
	return _info;
}
