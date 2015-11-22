#ifndef SRC_UTILS_F_ENTITY_ID_HPP
#define SRC_UTILS_F_ENTITY_ID_HPP
#include <cstdint>

namespace fengine
{
	class FEntityId
	{
	public:
		~FEntityId() = default;
		friend class FEntityIdManager;

		auto data() const noexcept { return data_; }
	private:
		explicit FEntityId(uint64_t id) : data_(id){}
		const uint64_t data_;
	};
}
#endif // SRC_UTILS_F_ENTITY_ID_HPP
