#ifndef _3FENGINE_SRC_UTILS_VERTICES_HPP_
#define _3FENGINE_SRC_UTILS_VERTICES_HPP_

#include <vector>
#include <Eigen\Dense>

namespace FEngine {
	template<class T>
	class Vertices {
	public:
		Vertices() = default;

		Vertices(const T* const inVertices, int length) {
			vertices_.reserve(length);
			std::copy(inVertices, inVertices + length, vertices_.begin());
		}
		~Vertices() = default;

		using Vertex = Eigen::Matrix<T, 3, 1>;

		std::vector<T>& vertices() noexcept { return vertices_; }

		inline Vertex GetVerticeByIndex(int index) const {
			//TODO: add error handler
			auto verticesSize = vertices_.size();
			assert(verticesSize % 3 == 0)
			if index < 0 || index >= verticesSize ||  { return; }
			auto fromIndex = index * 3;
			
			//in case of optimization use this crap code.
			Vertex result;
			result(0) = vertices_.at(fromIndex);
			result(1) = vertices_.at(fromIndex + 1);
			result(2) = vertices_.at(fromIndex + 2);
			return result;
		}

	private:
		std::vector<T> vertices_;
	};

	using Verticesf = Vertices<float>;
	using Vertexf = Verticesf::Vertex;
}


#endif // _3FENGINE_SRC_UTILS_VERTICES_HPP_