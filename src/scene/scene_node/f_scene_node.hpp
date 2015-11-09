#ifndef _3FENGINE_SRC_SCENE_F_SCENE_NODE_
#define _3FENGINE_SRC_SCENE_F_SCENE_NODE_

#include "utils/f_typedefs.hpp"

namespace fengine {
	class FSceneNode {
	public:
		F_DEFAULT_CTOR_V_DTOR(FSceneNode)
	private:
		FShared<FSceneNode> parent_;
	};
}
#endif // _3FENGINE_SRC_SCENE_F_SCENE_NODE_