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

		explicit FEntity(const FEntityId& id, const FEntityType& type, const FPos3f& pos, const FPoint3f& rotation, const FScale3f& scale);

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

		void set_position(const FPos3f& position);
		void set_scale(const FScale3f& scale);
		void set_rotation(const FPoint3f& rotation);

		void move(const FPos3f& dp);
		void rotate(const FQuaternionf& dr);
		void rotate(const Eigen::Vector3f& dr);
		void scale(const FScale3f& ds);

		const FPos3f& position() const { return this->position_; } 
		const FPoint3f& rotation() const { return this->rotation_; }
		const FScale3f& scale() const { return this->scale_; }
		const FMatrix4f& transform() const { return this->transform_old.matrix(); }

		template<typename T>
		static FShared<FEntity> FindEntityById(const FVector<FShared<T>>& entity_vec, uint64_t id)
		{
			LOG_IF(id < 0, FATAL) << "Unique id must be >= 0";
			auto result = std::find_if(entity_vec.cbegin(), entity_vec.cend(), [id](FShared<T> el) { return el->id() == id; });
			return (result == entity_vec.cend()) ? nullptr : std::static_pointer_cast<FEntity>(*result);
		}
		void UpdateTransform();
	protected:
		

		Eigen::Affine3f transform_old;
		FMatrix4f transform_;
		
	private:
		FPos3f position_;
		FPoint3f rotation_;
		FScale3f scale_;

		const FEntityId id_;
		FEntityType type_;
		// TODO: Fix circular dependency
		FShared<FEntity> parent_;
		FVector<FShared<FEntity>> children_;
	};
}
#endif // _3FENGINE_SRC_SCENE_F_ENTITY_