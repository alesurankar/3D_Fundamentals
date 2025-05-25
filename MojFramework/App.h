#pragma once
#include "Graphics.h"
#include "Vec2.h"
#include <vector>
#include "MyMath.h"

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
	/*  Moije Funkcije              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  Moji Parametri              */
	std::vector<Vec2> star;
	float theta = 0.0f;
	static constexpr float vRot = PI / 60.0f;
	static constexpr float radInner = 1.0f;
	static constexpr float radOuter = 2.0f;
	static constexpr int nflares = 5;
	static constexpr float size = 100.0f;
	/********************************/
};