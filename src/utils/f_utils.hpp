#ifndef _3FENGINE_SRC_UTILS_F_UTILS_HPP_
#define _3FENGINE_SRC_UTILS_F_UTILS_HPP_

#include "f_typedefs.hpp"

namespace fengine {
	namespace futils {
		inline FString ToLower(const FString & str)
		{
			auto lower_case = str;
			std::transform(lower_case.begin(), lower_case.end(), lower_case.begin(), ::tolower);
			return lower_case;
		}
	}
}

#endif  // _3FENGINE_SRC_UTILS_F_UTILS_HPP_
