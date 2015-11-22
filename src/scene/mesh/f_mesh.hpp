#ifndef _3FENGINE_SRC_SCENE_MESH_F_MESH_HPP_
#define _3FENGINE_SRC_SCENE_MESH_F_MESH_HPP_

#include "utils/f_typedefs.hpp"
#include "scene/mesh/f_mesh_lod.hpp"
#include "scene/entity/f_entity.hpp"
namespace fengine {
	class FMesh : public FEntity
	{
	public:
		F_DEFAULT_CTOR_V_DTOR(FMesh)
		
		explicit FMesh(uint64_t id, const FString& name);
		explicit FMesh(uint64_t id, const FString& name, const FPoint3f& transition, const FPoint3f& rotation, const FPoint3f& scale);
		FShared<FGeometry> GetGeometry(float distance) const;

		void AddLod(const FMeshLod& mesh_lod);
		void AddLods(const FVector<FMeshLod>& lods);
		void AddLod(float threshold, FShared<FGeometry> geometry);

	private:
		FSortedSet<FMeshLod, std::less<FMeshLod> > lods_;
	};
}

#endif // _3FENGINE_SRC_SCENE_MESH_F_MESH_HPP_