#ifndef _3FENGINE_SRC_SCENE_MESH_F_MESH_HPP_
#define _3FENGINE_SRC_SCENE_MESH_F_MESH_HPP_

#include "utils/f_typedefs.hpp"
#include "scene/mesh/f_mesh_lod.hpp"
#include "scene/f_entity.hpp"
#include "components/f_logger.hpp"

namespace fengine {
	class FMesh : public FEntity {
	public:
		F_DEFAULT_CTOR_V_DTOR(FMesh)

		const FShared<FGeometry> GetGeometry(float distance) const;
	private:
		FString name_;
		FVector<FMeshLod> lods_;
	};
}

#endif // _3FENGINE_SRC_SCENE_MESH_F_MESH_HPP_