#include "MainWindow.h"
#include "App.h"
#include "Mat3.h"


App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	cube(1.0f)
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
	const float dt = 1.0f / 60.0f;
	if (wnd.kbd.KeyIsPressed('Q'))
	{
		theta_x += dTheta * dt;
	}
	if (wnd.kbd.KeyIsPressed('W'))
	{
		theta_y += dTheta * dt;
	}
	if (wnd.kbd.KeyIsPressed('E'))
	{
		theta_z += dTheta * dt;
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		theta_x -= dTheta * dt;
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		theta_y -= dTheta * dt;
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		theta_z -= dTheta * dt;
	}
}

void App::ComposeFrame()
{
	auto lines = cube.GetLines();
	const Mat3 rot =
		Mat3::RotationX(theta_x) *
		Mat3::RotationY(theta_y) *
		Mat3::RotationZ(theta_z);
	for (auto& v : lines.vertices)
	{
		v *= rot;
		v += { 0.0f, 0.0f, 1.0f };
		cst.Transform(v);
	}
	for (auto i = lines.indices.cbegin(),
		end = lines.indices.cend();
		i != end; std::advance(i, 2))
	{
		gfx.DrawLine(lines.vertices[*i], lines.vertices[*std::next(i)], Colors::White);
	}
}