#include "f_mesh_lod.hpp"

namespace fengine {
	FMeshLod::FMeshLod(float threshold, FShared<FGeometry> geometry): threshold_(threshold), geometry_(geometry)
	{}

	bool FMeshLod::IsVisible(float distance) const
	{ return distance <= threshold_; }

	bool FMeshLod::IsValid() const
	{
		return threshold_ > 0 && geometry_;
	}
}