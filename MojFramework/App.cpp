#include "MainWindow.h"
#include "App.h"


App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
}

void App::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void App::UpdateModel()
{
}

#include "Mat3.h"
void App::ComposeFrame()
{
	Vec3 v(1.0f, 1.0f, 1.0f);
	Mat3 m = Mat3::Scaling(3.0f);
	v *= m;
}