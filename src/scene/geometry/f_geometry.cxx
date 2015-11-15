#include "f_geometry.hpp"

namespace fengine {
	FGeometry::FGeometry(
		const FVertices3f & vertices,
		const FIndices3 & indices,
		const FUvsf & uvs
		) : indices_(indices),vertices_(vertices), uvs_(uvs)
	{}
}