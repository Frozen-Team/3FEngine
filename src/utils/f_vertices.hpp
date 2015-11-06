#ifndef _3FENGINE_SRC_UTILS_F_VERTICES_HPP_
#define _3FENGINE_SRC_UTILS_F_VERTICES_HPP_

#include <vector>
#include <Eigen/Dense>

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

		FVertices(const Vector& in_vertices)
		{
			static_assert(base != 0, "Base size cannot be zero.");
			this->Add(in_vertices);
		}

		void Add(const Vector& to_insert)
		{
			auto to_insert_size = to_insert.size();
			assert(to_insert_size % base == 0);

			this->vertices_.reserve(this->vertices_.size() + to_insert_size);
			this->vertices_.insert(this->vertices_.end(), to_insert.cbegin(), to_insert.cend());

			this->points_count_ = to_insert_size / base;
		}

		Vector& vertices() noexcept { return vertices_; }

		int points_count() noexcept { return points_count_; }

		Vertex GetVerticeByIndex(int index) const
		{
			auto verticesSize = vertices_.size();
			if (index < 0 || index >= verticesSize)
			{ 
				LOG(FATAL) << "Index out of range";
			}
			auto fromIndex = index * base;

			Vertex result;
			for (int i = 0; i < base; i++) {
				result(i) = vertices_.at(fromIndex + i);
			}
			return result;
		}

	private:
		Vector vertices_;
		size_t points_count_;
	};
	
}


#endif // _3FENGINE_SRC_UTILS_F_VERTICES_HPP_