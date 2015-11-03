#include "f_mesh_lod.hpp"

namespace fengine {
	const bool FMeshLod::IsValid() const
	{
		return threshold_ > 0 && geometry_;
	}
}