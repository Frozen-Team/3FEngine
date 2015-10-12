#ifndef _3FENGINE_SRC_UTILS_VERTICES_HPP_
#define _3FENGINE_SRC_UTILS_VERTICES_HPP_

#include <vector>
#include <Eigen\Dense>

namespace FEngine {
	template<typename T, int base>
	class Vertices {
	public:
		Vertices() = default;
		~Vertices() = default;

		Vertices(const T* const inVertices, int length) {
			vertices_.reserve(length);
			std::copy(inVertices, inVertices + length, vertices_.begin());
		}
		
		using Vector = std::vector<T>;
		using Vertex = Eigen::Matrix<T, base, 1>;

		Vector& vertices() noexcept { return vertices_; }

		inline Vertex GetVerticeByIndex(int index) const {
			//TODO: add error handler
			auto verticesSize = vertices_.size();
			assert(verticesSize % base == 0)
			if index < 0 || index >= verticesSize ||  { return; }
			auto fromIndex = index * base;
			
			//for optimization purposes use this CRAP code.
			Vertex result;
			for (int i = 0; i < base; i++) {
				result(i) = vertices_.at(fromIndex + i);
			}
			return result;
		}

	private:
		Vector vertices_;
	};


	using Vertices3f = Vertices<float, 3>;
	using Vertex3f = Vertices3f::Vertex;
	
	//template<class T>

}


#endif // _3FENGINE_SRC_UTILS_VERTICES_HPP_