#include "pch.h"
#include "Exception.h"
#include "Keyboard.h"
#include "Mouse.h" 
#include "Graphics.h"

class Window
{
public:
	class WindowClass
	{
	public:
		static const char* GetName() { return _wndClass._wndClassName; }
		static HINSTANCE GetInstance() { return _wndClass._hInst; }

	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;

	private:
		static constexpr const char* _wndClassName = "Direct3D WindowClass";
		static WindowClass _wndClass;
		HINSTANCE _hInst;
	};

public:
	void Init(int width, int height, const char* name);
	~Window();

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

public:
	void SetTitle(const string& title);
	static optional<int> ProcessMessages();

public:
	Keyboard _keyboard;
	Mouse _mouse;
	HWND _hWnd;

private:
	int _width;
	int _height;
};