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

void App::ComposeFrame()
{
	Vec3 v0 = { 0.0f,0.5f,0.0f };
	Vec3 v1 = { 0.5f,-0.5f,0.0f };
	Vec3 v2 = { -0.5f,-0.5f,0.0f };
	gfx.DrawLine(cst.GetTransformed(v0), cst.GetTransformed(v1), Colors::White);
	gfx.DrawLine(cst.GetTransformed(v1), cst.GetTransformed(v2), Colors::White);
	gfx.DrawLine(cst.GetTransformed(v2), cst.GetTransformed(v0), Colors::White);
}