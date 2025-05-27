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
	const Vec2 v0(50.0f, 50.0f);
	const Vec2 v1(590.0f, 50.0f);
	const Vec2 v2(590.0f, 590.0f);
	const Vec2 v3(50.0f, 590.0f);

	const Vec2 u(wnd.mouse.GetPos());

	gfx.DrawTriangle(v0, v1, u, Colors::Red);
	gfx.DrawTriangle(v1, v2, u, Colors::White);
	gfx.DrawTriangle(v2, v3, u, Colors::Green);
	gfx.DrawTriangle(v3, v0, u, Colors::Blue);

	//auto lines = cube.GetLines();
	//const Mat3 rot =
	//	Mat3::RotationX( theta_x ) *
	//	Mat3::RotationY( theta_y ) *
	//	Mat3::RotationZ( theta_z );
	//for( auto& v : lines.vertices )
	//{
	//	v *= rot;
	//	v += { 0.0f,0.0f,offset_z };
	//	pst.Transform( v );
	//}
	//for( auto i = lines.indices.cbegin(),
	//	end = lines.indices.cend();
	//	i != end; std::advance( i,2 ) )
	//{
	//	gfx.DrawLine( lines.vertices[*i],lines.vertices[*std::next( i )],Colors::White );
	//}
}