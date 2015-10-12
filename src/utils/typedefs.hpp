#ifndef _3FENGINE_SRC_UTILS_TYPEDEFS_HPP_
#define _3FENGINE_SRC_UTILS_TYPEDEFS_HPP_

#include "vertices.hpp"

namespace FEngine {
	using Vertices3f = Vertices<float, 3>;
	using Vertex3f = Vertices3f::Vertex;

	using Indices3 = Vertices<int, 3>;
	using UVsf = Vertices<float, 2>;
}


#endif
