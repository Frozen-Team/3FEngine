#ifndef _3FENGINE_SRC_COMPONENTS_F_RESOURCES_LOADER_HPP_
#define _3FENGINE_SRC_COMPONENTS_F_RESOURCES_LOADER_HPP_

#include "fbxsdk.h"

#include "../utils/f_typedefs.hpp"
#include "../utils/f_singleton.hpp"

namespace fengine {
	class FResoucresLoader : public futils::FSingleton<FResoucresLoader>
	{
		F_DISABLE_COPY(FResoucresLoader)
	public:
		~FResoucresLoader() {};
	private:
		FResoucresLoader() {};
	};
}

#endif // _3FENGINE_SRC_COMPONENTS_F_RESOURCES_LOADER_HPP_
