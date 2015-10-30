#ifndef _3FENGINE_SRC_UTILS_F_TYPEDEFS_HPP_
#define _3FENGINE_SRC_UTILS_F_TYPEDEFS_HPP_

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <functional>

#include "Eigen/Dense"	
#include "boost/container/flat_set.hpp"

#include "f_vertices.hpp"

namespace fengine {
#define F_DISABLE_COPY(Class) \
	Class(const Class&) = delete; \
	Class& operator=(const Class&) = delete;

#define F_DEFAULT_CTOR_DTOR(Class) \
	Class() = default; \
	~Class() = default;

#define F_DEFAULT_CTOR_V_DTOR(Class) \
	Class() = default; \
	virtual ~Class() = default;
	
	using FPoint3f = Eigen::Matrix<float, 3, 1>;
	using FPoint2i = Eigen::Matrix<int, 2, 1>;

	template<class T>
	using FShared = std::shared_ptr<T>;

	template<class T>
	using FUnique = std::unique_ptr<T>;

	using FString = std::string;

	using FVertices3f = FVertices<float, 3>;
	using FVertex3f = FVertices3f::Vertex;	

	using FIndices3 = FVertices<int, 3>;
	using FUvsf = FVertices<float, 2>;

	template<typename T>
	using FVector = std::vector<T>;

	template<typename T, typename Compare = std::less<T>>
	using FSortedSet = boost::container::flat_set<T, Compare>;

	template<typename K, typename V>
	using FMap = std::map<K, V>;

	template<typename T>
	using FSet = std::set<T>;

	template<typename T>
	using FDeque = std::deque<T>;
}

#endif // _3FENGINE_SRC_UTILS_F_TYPEDEFS_HPP_
