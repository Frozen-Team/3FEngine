#ifndef _3FENGINE_SRC_SCENE_F_ENTITY_
#define _3FENGINE_SRC_SCENE_F_ENTITY_

#include "utils/f_typedefs.hpp"
#include "scene/geometry/f_transform_matrix.hpp"
#include "fcomponents/f_logger.hpp"

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
		FEntity(uint64_t id, const FString& name, const FEntityType& type, const FPoint3f& transition, const FPoint3f& rotation, const FPoint3f& scale);
		void AddChild(FShared<FEntity> child);

		FShared<FEntity> SearchInHierarchy(uint64_t id) const;
		FShared<FEntity> GetChild(uint64_t id) const;
		bool HasParent() const;

		void set_name(const FString& name);
		void set_parent(FShared<FEntity> parent);
		void set_id(uint64_t id);
		void set_type(FEntityType type);
		auto parent() const	{ return this->parent_; }
		auto children() const { return this->children_; }
		auto id() const { return this->id_; }
		auto name() const { return this->name_; }

		template<typename T>
		static FShared<FEntity> FindEntityById(const FVector<FShared<T>>& entity_vec, uint64_t id)
		{
			LOG_IF(id < 0, FATAL) << "Unique id must be >= 0";
			auto result = std::find_if(entity_vec.cbegin(), entity_vec.cend(), [id](FShared<T> el) { return el->id() == id; });
			return (result == entity_vec.cend()) ? nullptr : std::static_pointer_cast<FEntity>(*result);
		}
	private:
		uint64_t id_;
		FString name_;
		FEntityType type_;
		FShared<FEntity> parent_;
		FVector<FShared<FEntity>> children_;

	};
}
#endif // _3FENGINE_SRC_SCENE_F_ENTITY_