#include "pch.h"
#include "DxgiInfoManager.h"
#include "Window.h"
#include "Graphics.h"
#include "Exception.h"


DxgiInfoManager::DxgiInfoManager()
{
	typedef HRESULT (WINAPI* DXGIGetDebugInterface)(REFIID,void **);

	const auto hModDxgiDebug = LoadLibraryEx( "dxgidebug.dll",nullptr,LOAD_LIBRARY_SEARCH_SYSTEM32 );
	if( hModDxgiDebug == nullptr )
	{
		throw EXCEPTION();
	}

	// get address of DXGIGetDebugInterface in dll
	const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
		reinterpret_cast<void*>(GetProcAddress( hModDxgiDebug,"DXGIGetDebugInterface" ))
	);
	if( DxgiGetDebugInterface == nullptr )
	{
		throw LAST_EXCEPTION();
	}

	HRESULT hr;
	NOINFO_THROW_FAILED(DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), reinterpret_cast<void**>(&_dxgiInfoQueue)));
}

DxgiInfoManager::~DxgiInfoManager()
{
	if (_dxgiInfoQueue != nullptr)
		_dxgiInfoQueue->Release();
}

void DxgiInfoManager::Set()
{
	_next = _dxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
}

std::vector<std::string> DxgiInfoManager::GetMessages() const
{
	std::vector<std::string> messages;
	const auto end = _dxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	for (auto i = _next; i < end; i++)
	{
		HRESULT hr;
		SIZE_T messageLength;

		NOINFO_THROW_FAILED(_dxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength));
		
		auto bytes = std::make_unique<std::byte[]>(messageLength);
		auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
		// get the message and push its description into the std::vector
		NOINFO_THROW_FAILED(_dxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength));
		messages.emplace_back(pMessage->pDescription);
	}
	return messages;
}
