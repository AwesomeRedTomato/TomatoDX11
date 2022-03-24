#pragma once
#include "Window.h"

class App
{
public:
	App();

	int Go();

private:
	void Update();
	void Render();


private:
	Window _wnd;
};

