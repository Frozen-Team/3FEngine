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

			this->vec_.reserve(this->vec_.size() + to_insert_size);
			this->vec_.insert(this->vec_.end(), to_insert.cbegin(), to_insert.cend());

			this->points_count_ = vec_.size() / base;
		}

		const Vector& vec() const noexcept { return vec_; }

		int points_count() const noexcept { return points_count_; }

		Vertex GetVerticeByIndex(int index) const
		{
			auto verticesSize = vec_.size();
			if (index < 0 || index >= verticesSize)
			{ 
				LOG(FATAL) << "Index out of range";
			}
			auto fromIndex = index * base;

			Vertex result;
			for (auto i = 0; i < base; i++) {
				result(i) = vec_.at(fromIndex + i);
			}
			return result;
		}

	private:
		Vector vec_;
		size_t points_count_;
	};
	
}


#endif // _3FENGINE_SRC_UTILS_F_VERTICES_HPP_