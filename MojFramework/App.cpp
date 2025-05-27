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
		theta_x = wrap_angle(theta_x + dTheta * dt);
	}
	if (wnd.kbd.KeyIsPressed('W'))
	{
		theta_y = wrap_angle(theta_y + dTheta * dt);
	}
	if (wnd.kbd.KeyIsPressed('E'))
	{
		theta_z = wrap_angle(theta_z + dTheta * dt);
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		theta_x = wrap_angle(theta_x - dTheta * dt);
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		theta_y = wrap_angle(theta_y - dTheta * dt);
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		theta_z = wrap_angle(theta_z - dTheta * dt);
	}
	if (wnd.kbd.KeyIsPressed('R'))
	{
		offset_z += 2.0f * dt;
	}
	if (wnd.kbd.KeyIsPressed('F'))
	{
		offset_z -= 2.0f * dt;
	}
}

void App::ComposeFrame()
{
	auto triangles = cube.GetTriangles();
	const Mat3 rot =
		Mat3::RotationX(theta_x) *
		Mat3::RotationY(theta_y) *
		Mat3::RotationZ(theta_z);
	for (auto& v : triangles.vertices)
	{
		v *= rot;
		v += { 0.0f, 0.0f, offset_z };
		cst.Transform(v);
	}
	for (auto i = triangles.indices.cbegin(),
		end = triangles.indices.cend();
		i != end; std::advance(i, 3))
	{
		gfx.DrawTriangle(triangles.vertices[*i], triangles.vertices[*std::next(i)], triangles.vertices[*std::next(i, 2)], Colors::White);
	}
}