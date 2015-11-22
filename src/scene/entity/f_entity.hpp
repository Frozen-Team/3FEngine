#ifndef _3FENGINE_SRC_SCENE_F_ENTITY_
#define _3FENGINE_SRC_SCENE_F_ENTITY_

#include "utils/f_typedefs.hpp"
#include "scene/geometry/f_transform_matrix.hpp"
#include "fcomponents/f_logger.hpp"
#include <utils/f_entity_id.hpp>

namespace fengine {
	class FEntity 
	{
	public:
		enum class FEntityType
		{
			kMesh,
			kCamera,
			kUnknown, // neither known, nor set type
		};
		typedef FVector<FShared<FEntity>>::iterator iterator;
		typedef FVector<FShared<FEntity>>::const_iterator const_iterator;

		iterator begin() { return children_.begin(); }
		iterator end() { return children_.end(); }

		const_iterator cbegin() const { return children_.cbegin(); }
		const_iterator cend() const { return children_.cend(); }

		virtual ~FEntity() = default;
		explicit FEntity(const FEntityId& id, const FEntityType& type);
		explicit FEntity(const FEntityId& id, const FEntityType& type, const FPoint3f& transition, const FPoint3f& rotation, const FPoint3f& scale);
		void AddChild(FShared<FEntity> child);

		FShared<FEntity> SearchInHierarchy(uint64_t id) const;
		FShared<FEntity> GetChild(uint64_t id) const;
		bool HasParent() const;

		void set_name(const FString& name);
		void set_parent(FShared<FEntity> parent);
		void set_type(FEntityType type);
		auto parent() const	{ return this->parent_; }
		auto children() const { return this->children_; }
		auto id() const { return this->id_.data(); }

		void SetTransition(const FPoint3f& transition);
		void SetScale(const FPoint3f& scale);
		void SetRotation(const FPoint3f& rotation);

		FPoint3f GetTransition() const;
		FPoint3f GetScale() const;
		FPoint3f GetRotation() const;

		template<typename T>
		static FShared<FEntity> FindEntityById(const FVector<FShared<T>>& entity_vec, uint64_t id)
		{
			LOG_IF(id < 0, FATAL) << "Unique id must be >= 0";
			auto result = std::find_if(entity_vec.cbegin(), entity_vec.cend(), [id](FShared<T> el) { return el->id() == id; });
			return (result == entity_vec.cend()) ? nullptr : std::static_pointer_cast<FEntity>(*result);
		}
	protected:
		FMatrix4f view_;
	private:
		const FEntityId id_;
		FEntityType type_;
		// TODO: Fix circular dependency
		FShared<FEntity> parent_;
		FVector<FShared<FEntity>> children_;
		FTransformationMatrix transform_;
	};
}
#endif // _3FENGINE_SRC_SCENE_F_ENTITY_