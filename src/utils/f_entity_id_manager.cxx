#include "f_entity_id_manager.hpp"
#include <fcomponents/f_logger.hpp>

namespace fengine
{
	uint64_t FEntityIdManager::current_id_ = (std::numeric_limits<uint64_t>::max)();


	FEntityId FEntityIdManager::GenerateId()
	{
		LOG_IF(current_id_ == 0, FATAL) << "Too much entities were created";
		return FEntityId(current_id_--);
	}

	FEntityId FEntityIdManager::GenerateId(uint64_t id)
	{
		return FEntityId(id);
	}
}
