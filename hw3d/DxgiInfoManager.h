#pragma once
class DxgiInfoManager
{
public:
	DxgiInfoManager();
	~DxgiInfoManager();
	DxgiInfoManager(const DxgiInfoManager&) = delete;
	DxgiInfoManager& operator=(const DxgiInfoManager&) = delete;

public:
	void Set();
	std::vector<std::string> GetMessages() const;

private:
	ULONGLONG _next = 0;
	struct IDXGIInfoQueue* _dxgiInfoQueue = nullptr;
};