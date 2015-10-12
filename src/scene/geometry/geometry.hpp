#ifndef _3FENGINE_SRC_SCENE_GEOMETRY_GEOMETRY_HPP
#define _3FENGINE_SRC_SCENE_GEOMETRY_GEOMETRY_HPP

#include <vector>
#include "../../utils/typedefs.hpp"

namespace FEngine {
	class Geometry
	{
	public:
		Geometry() = default;
		virtual ~Geometry() {}

		inline Indices3& indices() { return indices_; }
	private:
		Indices3 indices_;
		Vertices3f vertices_;
		UVsf uvs_;
	};
}


#endif // _3FENGINE_SRC_SCENE_GEOMETRY_GEOMETRY_HPP

