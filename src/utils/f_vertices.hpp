#ifndef _3FENGINE_SRC_UTILS_F_VERTICES_HPP_
#define _3FENGINE_SRC_UTILS_F_VERTICES_HPP_

#include <vector>
#include <Eigen/Dense>

//#include "fcomponents/f_logger.hpp"

namespace fengine
{
	template<typename T, int base>
	class FVertices
	{
	public:
		FVertices() = default;
		~FVertices() = default;
		

		using Vector = std::vector <T>;
		using Vertex = Eigen::Matrix<T, base, 1>;

		FVertices(const Vector& inVertices)
		{
			static_assert(base != 0, "Base size cannot be zero.");
			auto inVerticesSize = static_cast<int>(inVertices.size());
			assert(inVerticesSize % base == 0);
			this->vertices_ = inVertices;
			this->points_count_ = inVerticesSize / base;
		}


		void Add(const Vector& args)
		{
			for (auto& el : args) {
				this->vertices_.push_back(el);
			}
		}
		inline Vector& vertices() noexcept { return vertices_; }
		inline int points_count() noexcept { return points_count_; }

		inline Vertex GetVerticeByIndex(int index) const
		{
			//TODO: add error handler
			auto verticesSize = vertices_.size();
			if index < 0 || index >= verticesSize || { return; }
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