#ifndef _3FENGINE_SRC_UTILS_F_VERTICES_HPP_
#define _3FENGINE_SRC_UTILS_F_VERTICES_HPP_

#include <vector>
#include <Eigen/Dense>

namespace fengine {
	template<typename T, int base>
	class FVertices {
	public:
		FVertices() = default;
		~FVertices() = default;

		FVertices(const T* const inVertices, int length) {
			assert(base);
			this->points_count_ = length / base;
			vertices_.reserve(length);
			std::copy(inVertices, inVertices + length, vertices_.begin());
		}
		
		using Vector = std::vector<T>;
		using Vertex = Eigen::Matrix<T, base, 1>;

		inline Vector& vertices() noexcept { return vertices_; }
		inline int points_count() noexcept { return points_count_; }

		inline Vertex GetVerticeByIndex(int index) const {
			//TODO: add error handler
			auto verticesSize = vertices_.size();
			assert(verticesSize % base == 0)
			if index < 0 || index >= verticesSize ||  { return; }
			auto fromIndex = index * base;
			
			Vertex result;
			for (int i = 0; i < base; i++) {
				result(i) = vertices_.at(fromIndex + i);
			}
			return result;
		}

	private:
		Vector vertices_;
		int points_count_;
	};
}


#endif // _3FENGINE_SRC_UTILS_F_VERTICES_HPP_