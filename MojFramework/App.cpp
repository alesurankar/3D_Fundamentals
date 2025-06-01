#include "MainWindow.h"
#include "App.h"
#include "Sphere.h"
#include "SpecularPhongPointScene.h"
#include <sstream>

App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	scenes.push_back(std::make_unique<SpecularPhongPointScene>(gfx, IndexedTriangleList<SpecularPhongPointScene::Vertex>::LoadNormals("models\\0BJ6.obj")));
	curScene = scenes.begin();
	OutputSceneName();
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
	const float dt = ft.CheckPoint();
	// cycle through scenes when tab is pressed
	while (!wnd.kbd.KeyIsEmpty())
	{
		const auto e = wnd.kbd.ReadKey();
		if (e.GetCode() == VK_TAB && e.IsPress())
		{
			CycleScenes();
		}
		else if (e.GetCode() == VK_ESCAPE && e.IsPress())
		{
			wnd.Kill();
		}
	}
	// update scene
	(*curScene)->Update(wnd.kbd, wnd.mouse, dt);
}

void App::CycleScenes()
{
	if (++curScene == scenes.end())
	{
		curScene = scenes.begin(); 
	}
	OutputSceneName();
}

void App::OutputSceneName() const
{
	std::stringstream ss;
	const std::string stars((*curScene)->GetName().size() + 4, '*');

	ss << stars << std::endl
		<< "* " << (*curScene)->GetName() << " *" << std::endl
		<< stars << std::endl;
	OutputDebugStringA(ss.str().c_str());
}

void App::ComposeFrame()
{
	(*curScene)->Draw();
}