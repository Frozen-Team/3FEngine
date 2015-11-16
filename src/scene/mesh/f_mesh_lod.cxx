#include "f_mesh_lod.hpp"

namespace fengine {
	FMeshLod::FMeshLod(float threshold, FShared<FGeometry> geometry): threshold_(threshold), geometry_(geometry)
	{}

	bool FMeshLod::IsVisible(float distance) const
	{ return distance <= threshold_; }

	bool FMeshLod::IsValid() const
	{
		// TODO: Threshold is can be == 0.0f, isn't it?
		return threshold_ > 0 && geometry_;
	}
}