#ifndef _3FENGINE_SRC_SCENE_MESH_F_MESH_HPP_
#define _3FENGINE_SRC_SCENE_MESH_F_MESH_HPP_

#include "utils/f_typedefs.hpp"
#include "scene/mesh/f_mesh_lod.hpp"
#include "scene/f_entity.hpp"

namespace fengine {
	class FMesh : public FEntity {
	public:
		F_DEFAULT_CTOR_V_DTOR(FMesh)

		const FShared<FGeometry> GetGeometry(float distance) const;
		void AddLod(float threshold, FShared<FGeometry> geometry);

	private:
		void SortLods();

	private:
		FString name_;
		FSortedSet<FMeshLod, std::less<FMeshLod> > lods_;
	};
}

#endif // _3FENGINE_SRC_SCENE_MESH_F_MESH_HPP_