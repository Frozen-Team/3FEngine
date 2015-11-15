#ifndef _GAME_SRC_SCENES_SCENE_ONE_CUBE_HPP
#define _GAME_SRC_SCENES_SCENE_ONE_CUBE_HPP

#include <scene/mesh/f_mesh.hpp>

class CubeOne : public fengine::FMesh
{
public:
	CubeOne();

	virtual ~CubeOne() = default;
};

#endif // _GAME_SRC_SCENES_SCENE_ONE_CUBE_HPP