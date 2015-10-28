#ifndef _3FENGINE_SRC_SCENE_MESH_F_MESH_LOD_HPP_
#define _3FENGINE_SRC_SCENE_MESH_F_MESH_LOD_HPP_

#include "scene/geometry/f_geometry.hpp"
#include "scene/mesh/f_range.hpp"
#include "utils/f_typedefs.hpp"

namespace fengine {
	class FMeshLod {
	public:
		F_DEFAULT_CTOR_DTOR(FMeshLod)

		bool IsVisible(float distance) const {
			return distance <= threshold_;
		}
		
		//const auto where_visible() const { return where_visible_; }
		const auto geometry() const { return geometry_; }
		const auto& name() const { return name_; }

		void set_geometry(FShared<FGeometry> geometry) { geometry_ = geometry; }
		void set_thresold(float threshold) { threshold_ = threshold; }
		//void set_where_active(const FRange& where_active) {	where_visible_ = where_active; }
		void set_name(const FString& lod_name) { name_ = lod_name; }
	private:

		
	private: 
		FString name_;
		float threshold_;
		//FRange where_visible_;
		FShared<FGeometry> geometry_;
	};
}

#endif // _3FENGINE_SRC_SCENE_MESH_F_MESH_LOD_HPP_