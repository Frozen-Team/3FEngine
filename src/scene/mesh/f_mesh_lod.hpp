#ifndef _3FENGINE_SRC_SCENE_MESH_F_MESH_LOD_HPP_
#define _3FENGINE_SRC_SCENE_MESH_F_MESH_LOD_HPP_

#include "scene/geometry/f_geometry.hpp"
#include "utils/f_typedefs.hpp"

namespace fengine {
	class FMeshLod {
		F_DEFAULT_CTOR_DTOR(FMeshLod)
	private:

		void set_treshold_m(float treshold) { threshold_ = treshold; }
	private:
		float threshold_;
		FGeometry geometry_;
	};
}

#endif // _3FENGINE_SRC_SCENE_MESH_F_MESH_LOD_HPP_