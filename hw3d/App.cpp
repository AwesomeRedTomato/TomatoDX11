#include "pch.h"
#include "App.h"
#include "Timer.h"
#include "Graphics.h"

float App::time = 0;

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
		Render();
	}
}

void App::Update()
{

	++time;
}

void App::Render()
{
	_wnd._gfx->RenderBegin();
	_wnd._gfx->DrawTriangle(GET_SINGLE(Timer)->Peek(), 0,0);
	_wnd._gfx->RenderEnd();
}