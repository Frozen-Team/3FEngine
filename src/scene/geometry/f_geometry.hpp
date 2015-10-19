#ifndef _3FENGINE_SRC_SCENE_GEOMETRY_F_GEOMETRY_HPP
#define _3FENGINE_SRC_SCENE_GEOMETRY_F_GEOMETRY_HPP

#include <vector>
#include "utils/f_typedefs.hpp"

namespace fengine {

	class FGeometry
	{
	public:
		FGeometry(const FIndices3& indices, const FVertices3f& vertices, const FUvsf& uvs);
		FGeometry() = default;
		virtual ~FGeometry() = default;
		FIndices3& indices() { return indices_; }
		FVertices3f& vertices() { return vertices_; }
		FUvsf& uvs() { return uvs_; }

		void set_indices(const FIndices3& indices) { indices_ = indices;	}
		void set_vertices(const FVertices3f& vertices) { vertices_ = vertices; }
		void set_uvs(const FUvsf& uvs) { uvs_ = uvs; }
	private:
		FIndices3 indices_;
		FVertices3f vertices_;
		FUvsf uvs_;
	};
	
}


#endif // _3FENGINE_SRC_SCENE_GEOMETRY_GEOMETRY_HPP

