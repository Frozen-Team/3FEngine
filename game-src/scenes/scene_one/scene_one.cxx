#include "scene_one.hpp"
#include "camera_one.hpp"
#include "cube_one.hpp"

SceneOne::SceneOne()
{
	Add(std::make_shared<CubeOne>());
	auto camera = std::make_shared<CameraOne>();
	Add(camera);
}
