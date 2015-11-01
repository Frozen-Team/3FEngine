#ifndef _3FENGINE_SRC_SCENE_MESH_F_MESH_HPP_
#define _3FENGINE_SRC_SCENE_MESH_F_MESH_HPP_

#include "utils/f_typedefs.hpp"
#include "scene/mesh/f_mesh_lod.hpp"
#include "scene/f_entity.hpp"

namespace fengine {
	class FMesh 
	{
	public:
		F_DEFAULT_CTOR_V_DTOR(FMesh)

		FMesh(const FPoint3f& position);
		const FPoint3f& position() { return position_; }
		const FShared<FGeometry> GetGeometry(float distance) const;
		void AddLod(float threshold, FShared<FGeometry> geometry);

	private:

	private:
		FString name_;
		FPoint3f position_;
		FSortedSet<FMeshLod, std::less<FMeshLod> > lods_;
	};
}

#endif // _3FENGINE_SRC_SCENE_MESH_F_MESH_HPP_