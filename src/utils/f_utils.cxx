#include "f_utils.hpp"
#include <algorithm>

namespace fengine 
{
	namespace futils 
	{
		FString ToLower(const FString& str)
		{
			auto lower_case = str;
			std::transform(lower_case.begin(), lower_case.end(), lower_case.begin(), ::tolower);
			return lower_case;
		}
	}
}