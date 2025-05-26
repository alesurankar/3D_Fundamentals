#include "MainWindow.h"
#include "App.h"


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
}

#include "CubeScreenTransformer.h"
#include "Cube.h"
void App::ComposeFrame()
{
	auto lines = cube.GetLines();
	for (auto& v : lines.vertices)
	{
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