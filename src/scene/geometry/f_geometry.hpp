#ifndef _3FENGINE_SRC_SCENE_GEOMETRY_F_GEOMETRY_HPP
#define _3FENGINE_SRC_SCENE_GEOMETRY_F_GEOMETRY_HPP

#include <vector>
#include "utils/f_typedefs.hpp"

namespace fengine {

	class FGeometry
	{
	public:
		FGeometry(const FVertices3f& vertices, const FIndices3& indices, const FUvsf& uvs, const FVertices3f& normals);
		FGeometry() = default;
		virtual ~FGeometry() = default;
		FIndices3& indices() { return indices_; }
		FVertices3f& vertices() { return vertices_; }
		FUvsf& uvs() { return uvs_; }

		void set_indices(const FIndices3& indices) { indices_ = indices;	}
		void set_vertices(const FVertices3f& vertices) { vertices_ = vertices; }
		void set_uvs(const FUvsf& uvs) { uvs_ = uvs; }
	private:
		FIndices3 indices_; // polygon vertices
		FVertices3f vertices_; // control points
		FUvsf uvs_; // uvs
		FVertices3f normals_; //
	};
	
}


#endif // _3FENGINE_SRC_SCENE_GEOMETRY_GEOMETRY_HPP

