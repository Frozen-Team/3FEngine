#ifndef SRC_UTILS_F_ENTITY_ID_MANAGER_HPP
#define SRC_UTILS_F_ENTITY_ID_MANAGER_HPP
#include <cstdint>
#include "f_singleton.hpp"
#include <utils/f_typedefs.hpp>
#include "f_entity_id.hpp"

namespace fengine
{
	class FEntityIdManager : private futils::FSingleton<FEntityIdManager>
	{
	public:
		friend class Engine;
		F_DEFAULT_CTOR_V_DTOR(FEntityIdManager)

		static FEntityId GenerateId();

		// for now this method generates FEntityId with specified id
		// maybe later fbx ids will be recalculated and stored based on our rules
		static FEntityId GenerateId(uint64_t id);

	private:
		static uint64_t current_id_;
	};
}
#endif // SRC_UTILS_F_ENTITY_ID_MANAGER_HPP