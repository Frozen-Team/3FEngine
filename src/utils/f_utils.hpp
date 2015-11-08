#ifndef _3FENGINE_SRC_UTILS_F_UTILS_HPP_
#define _3FENGINE_SRC_UTILS_F_UTILS_HPP_

#include "f_typedefs.hpp"
//#include <math.h>
//#include <algorithm>

namespace fengine
{
	namespace futils
	{
		inline FString ToLower(const FString & str)
		{
			auto lower_case = str;
			//std::transform(lower_case.begin(), lower_case.end(), lower_case.begin(), ::tolower);
			return lower_case;
		}
		inline float DegreesToRadians(float degrees)
		{
			return 0.0;
			//return degrees * M_PI / 180;
		}
	}
}

#endif  // _3FENGINE_SRC_UTILS_F_UTILS_HPP_
