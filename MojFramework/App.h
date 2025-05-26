#pragma once
#include "Graphics.h"
#include "Vec2.h"
#include "CubeScreenTransformer.h"
#include "Cube.h"

class App
{
public:
	App(class MainWindow& wnd);
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  Moje Funkcije               */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  Moji Parametri              */
	CubeScreenTransformer cst;
	Cube cube;
	/********************************/
};