#pragma once
#include "Vec3.h"
#include <vector>
#include "IndexedTriangleList.h"

class Cube
{
public:
	Cube(float size)
	{
		const float side = size / 2.0f;
		vertices.emplace_back(-side, -side, -side);
		vertices.emplace_back(side, -side, -side);
		vertices.emplace_back(-side, side, -side);
		vertices.emplace_back(side, side, -side);
		vertices.emplace_back(-side, -side, side);
		vertices.emplace_back(side, -side, side);
		vertices.emplace_back(-side, side, side);
		vertices.emplace_back(side, side, side);
	}
	IndexedTriangleList GetTriangles() const
	{
		return
		{
			vertices,{
			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4 }
		};
	}
private:
	std::vector<Vec3> vertices;
};