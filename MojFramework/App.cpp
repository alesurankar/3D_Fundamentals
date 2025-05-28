#include "MainWindow.h"
#include "App.h"
#include "SolidCubeScene.h"
#include "CubeOrderScene.h"
#include "ConHexScene.h"
#include "ConHexWireScene.h"
#include "XMutualScene.h"
#include "TexCubeScene.h"
#include "TexWrapCubeScene.h"
#include "FoldedCubeScene.h"
#include <sstream>


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
	scenes.push_back(std::make_unique<TexCubeScene>(2.0f));
	scenes.push_back(std::make_unique<TexWrapCubeScene>(2.0f));
	scenes.push_back(std::make_unique<TexWrapCubeScene>(6.0f));
	scenes.push_back(std::make_unique<FoldedCubeScene>());
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
	const float dt = 1.0f / 60.0f;
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
	(*curScene)->Draw(gfx);
}