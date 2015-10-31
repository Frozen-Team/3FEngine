#ifndef _3FENGINE_SRC_SCENE_F_ENTITY_
#define _3FENGINE_SRC_SCENE_F_ENTITY_

#include "utils/f_typedefs.hpp"
#include "scene/f_scene_node.hpp"

namespace fengine {
	class FEntity : public FSceneNode, public ex::Entity {
	public:
		F_DEFAULT_CTOR_V_DTOR(FEntity)

		FEntity(ex::EntityManager& emgr) : ex::Entity(emgr.create()) {}

	private:
	};
}
#endif // _3FENGINE_SRC_SCENE_F_ENTITY_