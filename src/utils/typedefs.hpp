#ifndef _3FENGINE_SRC_UTILS_TYPEDEFS_HPP_
#define _3FENGINE_SRC_UTILS_TYPEDEFS_HPP_

#include <memory>

#include "vertices.hpp"

namespace FEngine {
#define F_DISABLE_COPY(Class) \
	Class(const Class&); \
	Class& operator=(const Class&);

	template<class T>
	using FShared = typename std::shared_ptr<T>;

	template<class T>
	using FUnique = std::unique_ptr<T>;

	using Vertices3f = Vertices<float, 3>;
	using Vertex3f = Vertices3f::Vertex;

	using Indices3 = Vertices<int, 3>;
	using UVsf = Vertices<float, 2>;

}

#endif
