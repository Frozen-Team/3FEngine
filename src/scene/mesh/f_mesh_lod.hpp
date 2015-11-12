#ifndef _3FENGINE_SRC_SCENE_MESH_F_MESH_LOD_HPP_
#define _3FENGINE_SRC_SCENE_MESH_F_MESH_LOD_HPP_

#include "scene/geometry/f_geometry.hpp"
#include "scene/mesh/f_range.hpp"
#include "utils/f_typedefs.hpp"

/*
	Threshold logic for now:
	if a mesh contains only 1 mesh_lod, then threshold == 0
	otherwise holds max float
*/
namespace fengine {
	class FMeshLod {
	public:
		~FMeshLod() = default;
		explicit FMeshLod(float threshold = -1.0f, FShared<FGeometry> geometry = nullptr);

		bool IsVisible(float distance) const;
		bool IsValid() const;

		float threshold() const { return threshold_; }
		auto geometry() const { return geometry_; }

		void set_geometry(FShared<FGeometry> geometry) { geometry_ = geometry; }
		void set_thresold(float threshold) { threshold_ = threshold; }	

		bool operator<(const FMeshLod& mesh_lod) const {
			return this->threshold() < mesh_lod.threshold();
		}
	
	private: 
		float threshold_;
		FShared<FGeometry> geometry_;
	};
}

#endif // _3FENGINE_SRC_SCENE_MESH_F_MESH_LOD_HPP_