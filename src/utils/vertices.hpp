#ifndef _3FENGINE_SRC_UTILS_VERTICES_HPP_
#define _3FENGINE_SRC_UTILS_VERTICES_HPP_

#include <vector>
#include <Eigen\Dense>

namespace FEngine {
	template<class T>
	class Vertices {
	public:
		Vertices() = default;
		~Vertices() = default;

		using Vertex = Eigen::Matrix<T, 3, 1>;

		std::vector<T>& vertices() noexcept { return vertices_; }

		Vertex GetVerticeByIndex(int index) const {
			//TODO: add error handler
	
			assert(vertices_.size() % 3 == 0)
			if index < 0 || index >= vertices_.size() ||  { return; }
			auto fromIndex = index * 3;
			
			Vertex result;
		}

	private:
		std::vector<T> vertices_;

	};

	using Verticesf = Vertices<float>;
	using Vertexf = Verticesf::Vertex;
}


#endif // _3FENGINE_SRC_UTILS_VERTICES_HPP_