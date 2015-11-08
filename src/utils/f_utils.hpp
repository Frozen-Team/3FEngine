#ifndef _3FENGINE_SRC_UTILS_F_UTILS_HPP_
#define _3FENGINE_SRC_UTILS_F_UTILS_HPP_

#include "f_typedefs.hpp"
#include <math.h>

namespace fengine
{
	namespace futils
	{
		inline FString ToLower(const FString & str)
		{
			auto lower_case = str;
			std::transform(lower_case.begin(), lower_case.end(), lower_case.begin(), ::tolower);
			return lower_case;
		}
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
	}
}

#endif  // _3FENGINE_SRC_UTILS_F_UTILS_HPP_
