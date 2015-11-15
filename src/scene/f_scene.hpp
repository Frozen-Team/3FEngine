#ifndef _3FENGINE_SRC_SCENE_F_SCENE_
#define _3FENGINE_SRC_SCENE_F_SCENE_

#include <atomic>

#include "utils/f_typedefs.hpp"
#include "scene/mesh/f_mesh.hpp"
#include "scene/camera/f_camera.hpp"
#include "scene/scene_node/f_scene_node.hpp"

namespace fengine
{
	class FScene
	{
	public:
		F_DEFAULT_CTOR_V_DTOR(FScene)

		FShared<FEntity> FindEntityById(uint64_t id) const;

		void Add(FShared<FMesh> mesh) { this->meshes_.push_back(move(mesh)); }
		void Add(FShared<FCamera> camera) { this->cameras_.push_back(move(camera)); }
		void Add(FShared<FSceneNode> scene_node) { this->scene_nodes_.push_back(move(scene_node)); }

		//void set_busy() { is_loaded_.store(false); }
		//void set_free() { is_loaded_.store(true); }
		//bool is_loaded() const { return is_loaded_.load(); }
	private:
		//std::atomic<bool> is_loaded_;
		FVector<FShared<FMesh> > meshes_;
		FVector<FShared<FCamera> > cameras_;
		FVector<FShared<FSceneNode> > scene_nodes_;
	};
}

#endif //_3FENGINE_SRC_SCENE_F_SCENE_