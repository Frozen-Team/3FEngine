#ifndef _3FENGINE_SRC_SCENE_F_ENTITY_
#define _3FENGINE_SRC_SCENE_F_ENTITY_

#include "fbxsdk.h"
#include "utils/f_typedefs.hpp"
#include "scene/geometry/f_transform_matrix.hpp"
#include "scene/scene_node/f_scene_node.hpp"

namespace fengine {
	class FEntity : public FTransformationMatrix
	{
	public:
		typedef FVector<FShared<FEntity>>::iterator iterator;
		typedef FVector<FShared<FEntity>>::const_iterator const_iterator;

		iterator begin() { return children_.begin(); }
		iterator end() { return children_.end(); }

		const_iterator cbegin() const { return children_.cbegin(); }
		const_iterator cend() const { return children_.cend(); }

		virtual ~FEntity() = default;
		FEntity();

		void AddChild(FShared<FEntity> child);

		void set_parent(FShared<FEntity> parent);
		auto parent() const	{ return this->parent_; }
		auto children() const { return this->children_; }
	private:
		FShared<FEntity> parent_;
		FVector<FShared<FEntity>> children_;

	};
}
#endif // _3FENGINE_SRC_SCENE_F_ENTITY_