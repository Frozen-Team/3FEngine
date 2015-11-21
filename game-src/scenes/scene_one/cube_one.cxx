#include "cube_one.hpp"

CubeOne::CubeOne()
{
	fengine::FVertices3f vertices;
	vertices.Add({
		// front
		-0.3f, -0.3f,  0.3f,
		0.3f, -0.3f,  0.3f,
		0.3f,  0.3f,  0.3f,
		-0.3f,  0.3f,  0.3f,
		// back
		-0.3f, -0.3f, -0.3f,
		0.3f, -0.3f, -0.3f,
		0.3f,  0.3f, -0.3f,
		-0.3f,  0.3f, -0.3f,
	});
	fengine::FIndices3 indices;
	indices.Add(
	{
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,
	});

	fengine::FUvsf colors;
	colors.Add({
		// front colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
		// back colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
	});

	auto geometry = std::make_unique<fengine::FGeometry>(vertices, indices, colors);
	AddLod(0.1f, std::move(geometry));
}
