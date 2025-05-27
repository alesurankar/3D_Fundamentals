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
	const Color colors[12] = {
		   Colors::White,
		   Colors::Blue,
		   Colors::Cyan,
		   Colors::Gray,
		   Colors::Green,
		   Colors::Magenta,
		   Colors::LightGray,
		   Colors::Red,
		   Colors::Yellow,
		   Colors::White,
		   Colors::Blue,
		   Colors::Cyan
	};
	// generate indexed triangle list
	auto triangles = cube.GetTriangles();
	// generate rotation matrix from euler angles
	const Mat3 rot =
		Mat3::RotationX(theta_x) *
		Mat3::RotationY(theta_y) *
		Mat3::RotationZ(theta_z);
	// transform from model space -> world (/view) space
	for (auto& v : triangles.vertices)
	{
		v *= rot;
		v += { 0.0f, 0.0f, offset_z };
	}
	// backface culling test (must be done in world (/view) space)
	for (size_t i = 0,
		end = triangles.indices.size() / 3;
		i < end; i++)
	{
		const Vec3& v0 = triangles.vertices[triangles.indices[i * 3]];
		const Vec3& v1 = triangles.vertices[triangles.indices[i * 3 + 1]];
		const Vec3& v2 = triangles.vertices[triangles.indices[i * 3 + 2]];
		triangles.cullFlags[i] = (v1 - v0) % (v2 - v0) * v0 > 0.0f;
	}
	// transform to screen space (includes perspective transform)
	for (auto& v : triangles.vertices)
	{
		cst.Transform(v);
	}
		// draw the mf triangles!
		for (size_t i = 0,
			end = triangles.indices.size() / 3;
			i < end; i++)
		{
			// skip triangles previously determined to be back-facing
			if (!triangles.cullFlags[i])
			{
				gfx.DrawTriangle(
					triangles.vertices[triangles.indices[i * 3]],
					triangles.vertices[triangles.indices[i * 3 + 1]],
					triangles.vertices[triangles.indices[i * 3 + 2]],
					colors[i]);
			}
		}
}