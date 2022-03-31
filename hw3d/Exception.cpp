#include "pch.h"
#include "Exception.h"

Exception::Exception(int line, const char* file) noexcept
	:
	_line(line), _file(file)
{
}

const char* Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << "Exception" << std::endl << GetOriginString();
	
	return oss.str().c_str();
}

std::string Exception::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << _file << "[Line] " << _line << std::endl;

	return oss.str();
}

WinException::WinException(int line, const char* file, HRESULT hr) noexcept
	:
	Exception(line, file), _hr(hr)
{
}

const char* WinException::what() const noexcept
{
	std::ostringstream oss;
	oss << "HrException" << std::endl << "[ErrorCode] " << _hr << std::endl <<
		"[Description] " << TranslateErrorCode(_hr) << std::endl;

	return oss.str().c_str();
}

std::string WinException::TranslateErrorCode(HRESULT hr) const noexcept
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

	std::string errorString = msgBuffer;
	LocalFree(msgBuffer);

	return errorString;
}

HrException::HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs) noexcept
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
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Error String] " << GetErrorString() << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl;
	if (!_info.empty())
	{
		oss << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
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

std::string HrException::GetErrorString() const noexcept
{
	return DXGetErrorString(_hr);
}

std::string HrException::GetErrorDescription() const noexcept
{
	char buffer[512];
	DXGetErrorDescription(_hr, buffer, sizeof(buffer));
	return buffer;
}

std::string HrException::GetErrorInfo() const noexcept
{
	return _info;
}
