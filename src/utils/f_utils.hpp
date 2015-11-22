#ifndef _3FENGINE_SRC_UTILS_F_UTILS_HPP_
#define _3FENGINE_SRC_UTILS_F_UTILS_HPP_

#include <cmath>
#include <limits>
#include <iomanip>
#include <math.h>

#include "f_typedefs.hpp"

namespace fengine
{
	namespace futils
	{
		FString ToLower(const FString & str);
		
		template<typename T>
		inline T DegreesToRadians(T degrees)
		{
			return static_cast<T>(degrees * M_PI / 180);
		}

		template<typename T>
		inline T InchToMeters(T inches)
		{
			return inches * 0.0254;
		}

		template<class T>
		typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type 
			almost_equal(T x, T y, int ulp)
		{
			return std::abs(x - y) < std::numeric_limits<T>::epsilon() * std::abs(x + y) * ulp
				|| std::abs(x - y) < (std::numeric_limits<T>::min)();
		}
	}
}

#endif  // _3FENGINE_SRC_UTILS_F_UTILS_HPP_
