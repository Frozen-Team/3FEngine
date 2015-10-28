#ifndef _3FENGINE_SRC_SCENE_MESH_F_RANGE_HPP_
#define _3FENGINE_SRC_SCENE_MESH_F_RANGE_HPP_

#include "components/f_logger.hpp"
#include "utils/f_typedefs.hpp"

namespace fengine {
	class FRange {
	public:
		F_DEFAULT_CTOR_DTOR(FRange)

		FRange(float from, float to) {
			this->SetRange(from, to);
		}

		void SetRange(float from, float to) {
			LOG_IF(from > to, FATAL);
			this->from_ = from;
			this->to_ = to;
		}
		
		bool IsInRange(float value) const { return ((from_ <= value) && (value <= to_)); }

		float from() { return from_; }
		float to() { return to_; }
	private:
		float from_;
		float to_;
	};
}
#endif // _3FENGINE_SRC_SCENE_MESH_F_RANGE_HPP_