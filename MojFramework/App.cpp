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
#include "Cube.h"
void App::ComposeFrame()
{
	CubeScreenTransformer cst;
	Cube c(1.0f);
	auto lines = c.GetLines();
	for (auto& v : lines.vertices)
	{
		cst.Transform(v);
	}
	for (auto i = lines.indices.cbegin(),
		end = lines.indices.cend();
		i != end; std::advance(i, 2))
	{
		gfx.DrawLine(lines.vertices[*i], lines.vertices[*std::next(i)], Colors::White);
	}
}