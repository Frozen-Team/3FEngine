#ifndef _3FENGINE_SRC_SCENE_GEOMETRY_GEOMETRY_HPP
#define _3FENGINE_SRC_SCENE_GEOMETRY_GEOMETRY_HPP

#include <vector>

namespace FEngine {
	class Geometry
	{
	public:
		Geometry() = default;
		virtual ~Geometry() {}

		inline std::vector<unsigned int>& indices() { return indices_; }
	private:
		std::vector<unsigned int> indices_;
		std::vector<float> vertices_;
		std::vector<float> uvs_;
	};
}


#endif // _3FENGINE_SRC_SCENE_GEOMETRY_GEOMETRY_HPP

