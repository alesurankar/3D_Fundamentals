#include "MainWindow.h"
#include "App.h"
#include "CubeScene.h"

App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	//scenes.push_back(std::make_unique<SolidCubeScene>());
	scenes.push_back(std::make_unique<CubeScene>(gfx, L"images\\office_skin.jpg"));
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
	const float dt = ft.Mark();
	(*curScene)->Update(wnd.kbd, wnd.mouse, dt);
	
}

void App::ComposeFrame()
{
	(*curScene)->Draw();
}