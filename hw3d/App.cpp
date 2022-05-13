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
	GET_SINGLE(Timer)->Mark();
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
	std::string titleTimer = std::to_string(GET_SINGLE(Timer)->Peek());
	_wnd.SetTitle("DirectX 11     Time: " + titleTimer);
}

void App::Render()
{
	_gfx->RenderBegin();
	_gfx->Update();
	_gfx->RenderEnd();
}