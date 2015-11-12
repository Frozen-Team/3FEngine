#ifndef _3FENGINE_SRC_SCENE_F_ENTITY_
#define _3FENGINE_SRC_SCENE_F_ENTITY_

#include "utils/f_typedefs.hpp"
#include "scene/geometry/f_transform_matrix.hpp"

namespace fengine {
	class FEntity : public FTransformationMatrix
	{
	public:
		enum class FEntityType
		{
			kMesh,
			kCamera,
			kNull, // neither known, nor set type
		};
		typedef FVector<FShared<FEntity>>::iterator iterator;
		typedef FVector<FShared<FEntity>>::const_iterator const_iterator;

		iterator begin() { return children_.begin(); }
		iterator end() { return children_.end(); }

		const_iterator cbegin() const { return children_.cbegin(); }
		const_iterator cend() const { return children_.cend(); }

		virtual ~FEntity() = default;
		FEntity();
		FEntity(uint64_t id, FEntityType type, const FPoint3f& transition, const FPoint3f& rotation, const FPoint3f& scale);
		void AddChild(FShared<FEntity> child);

		void set_parent(FShared<FEntity> parent);
		void set_id(uint64_t id);
		auto parent() const	{ return this->parent_; }
		auto children() const { return this->children_; }
	private:
		uint64_t id_;
		FEntityType type_;
		FShared<FEntity> parent_;
		FVector<FShared<FEntity>> children_;

	};
}
#endif // _3FENGINE_SRC_SCENE_F_ENTITY_