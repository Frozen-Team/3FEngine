#ifndef _3FENGINE_SRC_SCENE_GEOMETRY_F_GEOMETRY_HPP
#define _3FENGINE_SRC_SCENE_GEOMETRY_F_GEOMETRY_HPP

#include <vector>
#include "../../utils/f_typedefs.hpp"

namespace FEngine {
	class FGeometry
	{
	public:
		FGeometry() = default;
		virtual ~FGeometry() {}

		inline FIndices3& indices() { return indices_; }
	private:
		FIndices3 indices_;
		FVertices3f vertices_;
		FUVsf uvs_;
	};
}


#endif // _3FENGINE_SRC_SCENE_GEOMETRY_GEOMETRY_HPP

