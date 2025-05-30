#include "MainWindow.h"
#include "App.h"
#include "CubeSkinScene.h"
#include "CubeVertexColorScene.h"
#include "CubeSolidScene.h"
#include "DoubleCubeScene.h"
#include "VertexWaveScene.h"
#include "CubeVertexPositionColorScene.h"
#include "CubeSolidGeometryScene.h"
#include "CubeFlatIndependentScene.h"
#include "GeometryFlatScene.h"
#include "Sphere.h"
#include <sstream>


App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	scenes.push_back(std::make_unique<GeometryFlatScene>(gfx, Sphere::GetPlain<GeometryFlatScene::Vertex>()));
	scenes.push_back(std::make_unique<VertexWaveScene>(gfx));
	scenes.push_back(std::make_unique<GeometryFlatScene>(gfx,
		IndexedTriangleList<GeometryFlatScene::Vertex>::Load("models\\character_1.obj")));
	scenes.push_back(std::make_unique<GeometryFlatScene>(gfx, Cube::GetPlain<GeometryFlatScene::Vertex>()));
	scenes.push_back(std::make_unique<CubeFlatIndependentScene>(gfx));
	scenes.push_back(std::make_unique<CubeSolidGeometryScene>(gfx));
	scenes.push_back(std::make_unique<CubeVertexPositionColorScene>(gfx));
	scenes.push_back(std::make_unique<DoubleCubeScene>(gfx));
	scenes.push_back(std::make_unique<CubeSkinScene>(gfx, L"images\\office_skin.jpg"));
	scenes.push_back(std::make_unique<CubeVertexColorScene>(gfx));
	scenes.push_back(std::make_unique<CubeSolidScene>(gfx));
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