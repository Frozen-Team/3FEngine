#include <algorithm>

#include "f_mesh.hpp"
#include "components/f_logger.hpp"

namespace fengine {
	const FShared<FGeometry> FMesh::GetGeometry(float distance) const
	{
		LOG_IF(lods_.size() == 0, FATAL);
		auto& found = std::find_if(lods_.cbegin(), lods_.cend(), [distance](const FMeshLod& lod) { return lod.IsVisible(distance); });
		if (found != lods_.cend()) {
			return found->geometry();
		}
		return lods_.back;
	}
}

