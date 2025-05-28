#include "MainWindow.h"
#include "App.h"
#include "SolidCubeScene.h"
#include "CubeOrderScene.h"
#include "ConHexScene.h"
#include "ConHexWireScene.h"
#include "XMutualScene.h"
#include "TexCubeScene.h"


App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	scenes.push_back(std::make_unique<SolidCubeScene>()); 
	scenes.push_back(std::make_unique<CubeOrderScene>());
	scenes.push_back(std::make_unique<ConHexScene>());
	scenes.push_back(std::make_unique<ConHexWireScene>());
	scenes.push_back(std::make_unique<XMutualScene>());
	scenes.push_back(std::make_unique<TexCubeScene>());
	curScene = scenes.begin();
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
	// cycle through scenes when tab is pressed
	while (!wnd.kbd.KeyIsEmpty())
	{
		const auto e = wnd.kbd.ReadKey();
		if (e.GetCode() == VK_TAB && e.IsPress())
		{
			CycleScenes();
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
}

void App::ComposeFrame()
{
	(*curScene)->Draw(gfx);
}