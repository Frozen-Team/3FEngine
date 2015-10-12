#include "utils.hpp"
#include <algorithm>

namespace FEngine {
	namespace Utils {
		std::string ToLower(const std::string & str)
		{
			auto lower_case = str;
			std::transform(lower_case.begin(), lower_case.end(), lower_case.begin(), ::tolower);
			return lower_case;
		}
	}
}