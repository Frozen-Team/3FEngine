#ifndef _3FENGINE_SRC_SCENE_F_SCENE_
#define _3FENGINE_SRC_SCENE_F_SCENE_


#include "utils/f_typedefs.hpp"
#include "scene/mesh/f_mesh.hpp"
#include "scene/camera/f_camera.hpp"
#include "scene/scene_node/f_scene_node.hpp"

namespace fengine {
	class FScene{
	public:
		F_DEFAULT_CTOR_DTOR(FScene)


		void Add(FShared<FMesh> mesh) { this->meshes_.push_back(std::move(mesh)); }
		void Add(FShared<FCamera> camera) { this->cameras_.push_back(std::move(camera)); }
		void Add(FShared<FSceneNode> scene_node) { this->scene_nodes_.push_back(std::move(scene_node)); }

	private:
		FVector<FShared<FMesh> > meshes_;
		FVector<FShared<FCamera> > cameras_;
		FVector<FShared<FSceneNode> > scene_nodes_;
	};
}

#endif //_3FENGINE_SRC_SCENE_F_SCENE_