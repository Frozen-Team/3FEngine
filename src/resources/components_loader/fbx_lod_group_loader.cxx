#include "fbx_lod_group_loader.hpp"
#include <utils/f_typedefs.hpp>

namespace fengine
{
	float FbxLodGroupLoader::RetrieveThreshold(int index) const
	{
		FbxDistance threshold;
		auto result = this->GetThreshold(index, threshold);
		return result ? threshold.value() : FLT_MAX;
	}
}
