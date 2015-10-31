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

		FVertices(const T* const inVertices, int length);
		
		using Vector = std::vector<T>;
		using Vertex = Eigen::Matrix<T, base, 1>;

		inline Vector& vertices() noexcept { return vertices_; }
		inline int points_count() noexcept { return points_count_; }

		inline Vertex GetVerticeByIndex(int index) const;

	private:
		Vector vertices_;
		int points_count_;
	};
	
}


#endif // _3FENGINE_SRC_UTILS_F_VERTICES_HPP_