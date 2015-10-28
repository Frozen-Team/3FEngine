#ifndef _3FENGINE_SRC_SCENE_MESH_F_MESH_HPP_
#define _3FENGINE_SRC_SCENE_MESH_F_MESH_HPP_

#include "utils/f_typedefs.hpp"
#include "scene/mesh/f_mesh_lod.hpp"
#include "scene/f_entity.hpp"

namespace fengine {
	class FMesh : public FEntity {
	public:
		F_DEFAULT_CTOR_V_DTOR(FMesh)
		
		
	private:
		FString name_;
		FVector<FMeshLod> lods_;
	};
}

#endif // _3FENGINE_SRC_SCENE_MESH_F_MESH_HPP_