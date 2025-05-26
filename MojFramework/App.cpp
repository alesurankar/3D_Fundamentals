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

#include "CubeScreenTransformer.h"
void App::ComposeFrame()
{
	CubeScreenTransformer pst;
	Vec3 v0 = { 0.0f,0.5f,0.0f };
	Vec3 v1 = { 0.5f,-0.5f,0.0f };
	Vec3 v2 = { -0.5f,-0.5f,0.0f };
	gfx.DrawLine(pst.GetTransformed(v0), pst.GetTransformed(v1), Colors::White);
	gfx.DrawLine(pst.GetTransformed(v1), pst.GetTransformed(v2), Colors::White);
	gfx.DrawLine(pst.GetTransformed(v2), pst.GetTransformed(v0), Colors::White);
}