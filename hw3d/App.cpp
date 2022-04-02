#include "pch.h"
#include "App.h"
#include "Timer.h"
#include "Graphics.h"
#include "GDIPlusManager.h"

GDIPlusManager gdipm;

App::App()
{
	_wnd.Init(800, 600, "DirectX 11");
	_gfx->Init(_wnd);
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

}

void App::Render()
{
	_gfx->RenderBegin();
	_gfx->DrawTriangle(GET_SINGLE(Timer)->Peek(), 0,0);
	_gfx->RenderEnd();
}