#include <algorithm>

#include "f_mesh.hpp"
#include "fcomponents/f_logger.hpp"
#include "scene/components/components.hpp"

namespace fengine {
	FMesh::FMesh(ex::EntityManager & entity_manager, const FPoint3f& position) : FEntity(entity_manager)
	{
		this->assign<Position>(position);
	}

	const FPoint3f & FMesh::GetPosition()
	{
		auto pos = this->component<Position>();
		LOG_IF(!pos, FATAL) << "Cannot retrieve the position from the mesh";
		return pos.get()->pos();
	}

	const FShared<FGeometry> FMesh::GetGeometry(float distance) const
	{
		LOG_IF(lods_.size() == 0, FATAL) << "There is no LOD for current mesh";
		auto& found = std::find_if(lods_.cbegin(), lods_.cend(), [distance](const FMeshLod& lod) { return lod.IsVisible(distance); });
		if (found != lods_.cend()) {
			return found->geometry();
		}
		return lods_.nth(lods_.size() - 1).get_ptr()->geometry();
	}

	void FMesh::AddLod(float threshold, FShared<FGeometry> geometry)
	{	
		LOG_IF(threshold < 0 || !geometry, FATAL);
		auto is_inserted = this->lods_.insert(FMeshLod(threshold, geometry));
		LOG_IF(!is_inserted.second, FATAL) << "Failed to add LOD to mesh";
	}
}

