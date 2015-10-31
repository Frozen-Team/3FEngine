#include "f_vertices.hpp"

#include "fcomponents/f_logger.hpp"

namespace fengine {
	template<typename T, int base>
	inline FVertices<T, base>::FVertices(const T * const inVertices, int length)
	{
		LOG_IF(base <= 0, FATAL) << "Base must be bigger than 0"
			this->points_count_ = length / base;
		vertices_.reserve(length);
		std::copy(inVertices, inVertices + length, vertices_.begin());
	}

	template<typename T, int base>
	inline typename FVertices<T, base>::Vertex FVertices<T, base>::GetVerticeByIndex(int index) const
	{
		//TODO: add error handler
		auto verticesSize = vertices_.size();
		LOG_IF(verticesSize % base == 0, FATAL) << "Vertices size has to be divisible by base"
		if index < 0 || index >= verticesSize || { return; }
		auto fromIndex = index * base;

		Vertex result;
		for (int i = 0; i < base; i++) {
			result(i) = vertices_.at(fromIndex + i);
		}
		return result;
	}

}