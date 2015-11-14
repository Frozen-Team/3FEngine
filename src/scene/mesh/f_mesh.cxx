#include <algorithm>

#include "f_mesh.hpp"
#include "fcomponents/f_logger.hpp"

namespace fengine {
	FMesh::FMesh(uint64_t id, const FString& name, const FPoint3f& transition, const FPoint3f& rotation, const FPoint3f& scale) :
		FEntity(id, name, FEntityType::kMesh, transition, rotation, scale)
	{
	}

	FShared<FGeometry> FMesh::GetGeometry(float distance) const
	{
		LOG_IF(lods_.size() == 0, FATAL) << "There is no LOD for current mesh";
		auto& found = std::find_if(lods_.cbegin(), lods_.cend(), [distance](const FMeshLod& lod) { return lod.IsVisible(distance); });
		if (found != lods_.cend()) {
			return found->geometry();
		}
		return lods_.nth(lods_.size() - 1).get_ptr()->geometry();
	}

	void FMesh::AddLod(const FMeshLod & mesh_lod)
	{
		if (!mesh_lod.IsValid()) {
			LOG(ERROR) << "Mesh lod is not valid";
		}
		auto is_inserted = this->lods_.insert(mesh_lod);
		LOG_IF(!is_inserted.second, FATAL) << "Failed to add LOD to mesh";
		
	}

	void FMesh::AddLods(const FVector<FMeshLod>& lods)
	{
		this->lods_.reserve(this->lods_.size() + lods.size());
		for (const auto& lod : lods)
		{
			this->AddLod(lod);
		}
	}

	void FMesh::AddLod(float threshold, FShared<FGeometry> geometry)
	{	
		this->AddLod(FMeshLod(threshold, geometry));
	}
}

