#include "pch.h"
#include "App.h"

App::App()
	:
	_wnd(800, 600, "DirectX 11")
{
}

int App::Go()
{
	while (true)
	{
		if (const auto ecode = Window::ProcessMessages())
		{
			return *ecode;
		}
		Update();
	}
}

void App::Update()
{
	_wnd._gfx->RenderBegin();
	_wnd._gfx->RenderEnd();
}
