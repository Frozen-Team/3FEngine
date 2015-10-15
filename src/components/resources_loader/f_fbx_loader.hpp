#ifndef _3FENGINE_SRC_COMPONENTS_F_FBX_LOADER_HPP_
#define _3FENGINE_SRC_COMPONENTS_F_FBX_LOADER_HPP_

#include "fbxsdk.h"

#include "../../utils/f_typedefs.hpp"
#include "../../utils/f_singleton.hpp"

namespace fengine {
	class FFbxLoader : public futils::FSingleton<FFbxLoader>
	{
		F_DISABLE_COPY(FFbxLoader)
	public:
		~FFbxLoader() = default;
		FFbxLoader() = default;
	private:
		
	};
}

#endif // _3FENGINE_SRC_COMPONENTS_F_FBX_LOADER_HPP_
