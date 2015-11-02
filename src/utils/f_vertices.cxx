#include "f_vertices.hpp"

#include "fcomponents/f_logger.hpp"

namespace fengine {
	template<typename T, int base>
	FVertices<T, base>::FVertices(const Vector& inVertices)
	{
		auto inVerticesSize = inVertices.size();
		LOG_IF(inVerticesSize % base == 0, FATAL) << "Vertices size has to be divisible by base";
		this->vertices_ = inVertices;
		this->points_count = inVerticesSize / base;
	}

	template<typename T, int base>
	void FVertices<T, base>::Add(const Vector& args)
	{
		for (auto& el : args) {
			this->vertices_.push_back(el);
		}
	}

	template<typename T, int base>
	inline typename FVertices<T, base>::Vertex FVertices<T, base>::GetVerticeByIndex(int index) const
	{
		//TODO: add error handler
		auto verticesSize = vertices_.size();
		LOG_IF(verticesSize % base == 0, FATAL) << "Vertices size has to be divisible by base";
		if index < 0 || index >= verticesSize || { return; }
		auto fromIndex = index * base;

		Vertex result;
		for (int i = 0; i < base; i++) {
			result(i) = vertices_.at(fromIndex + i);
		}
		return result;
	}

}