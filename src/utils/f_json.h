#ifndef _3FENGINE_SRC_UTILS_F_JSON_HPP_
#define _3FENGINE_SRC_UTILS_F_JSON_HPP_

#include "rapidjson\document.h"
#include "utils\f_typedefs.hpp"

namespace fengine {

	namespace rj = rapidjson;

	class FJson : public rapidjson::Document
	{
		F_DISABLE_COPY(FJson)
	public:
		FJson() {}
		~FJson() {}

		int LoadFile(const FString& file_name);

	};
}
#endif // _3FENGINE_SRC_UTILS_F_JSON_HPP_