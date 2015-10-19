#include "f_geometry.hpp"

namespace fengine {
	FGeometry::FGeometry(
		const FIndices3 & indices, 
		const FVertices3f & vertices,
		const FUvsf & uvs
		) : indices_(indices),vertices_(vertices), uvs_(uvs)
	{
	}
}