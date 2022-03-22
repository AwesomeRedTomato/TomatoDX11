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
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

public:
	void SetTitle(const string& title);
	static optional<int> ProcessMessages();

public:
	unique_ptr<Graphics> _gfx;
	Keyboard _keyboard;
	Mouse _mouse;

private:
	int _width;
	int _height;
	HWND _hWnd;
};