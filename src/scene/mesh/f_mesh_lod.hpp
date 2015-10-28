#ifndef _3FENGINE_SRC_SCENE_MESH_F_MESH_LOD_HPP_
#define _3FENGINE_SRC_SCENE_MESH_F_MESH_LOD_HPP_

#include "scene/geometry/f_geometry.hpp"
#include "scene/mesh/f_range.hpp"
#include "utils/f_typedefs.hpp"

namespace fengine {
	class FMeshLod {
		F_DEFAULT_CTOR_DTOR(FMeshLod)
	public:
		bool IsVisible(float distance) {
			return where_visible_.IsInRange(distance);
		}
		
		auto where_visible() { return where_visible_; }
		auto geometry() { return geometry_; }
		FString& name() { return name_; }

		void set_geometry(FShared<FGeometry> geometry) { geometry_ = geometry; }
		void set_where_active(const FRange& where_active) {	where_visible_ = where_active; }
		void set_name(const FString& lod_name) { name_ = lod_name; }
	private:

		
	private: 
		FString name_;
		FRange where_visible_;
		FShared<FGeometry> geometry_;
	};
}

#endif // _3FENGINE_SRC_SCENE_MESH_F_MESH_LOD_HPP_