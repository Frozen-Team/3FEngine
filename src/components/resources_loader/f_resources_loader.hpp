#ifndef _3FENGINE_SRC_COMPONENTS_F_RESOURCES_LOADER_HPP_
#define _3FENGINE_SRC_COMPONENTS_F_RESOURCES_LOADER_HPP_

#include "../../utils/f_typedefs.hpp"
#include "../../utils/f_singleton.hpp"
#include "f_fbx_loader.hpp"

namespace fengine {
	class FResoucresLoader : public futils::FSingleton<FResoucresLoader>
	{
		F_DISABLE_COPY(FResoucresLoader)
	public:
		~FResoucresLoader() = default;
		FResoucresLoader() = delete;
	private:
		FFbxLoader fbx_loader_;
	};
}

#endif // _3FENGINE_SRC_COMPONENTS_F_RESOURCES_LOADER_HPP_
