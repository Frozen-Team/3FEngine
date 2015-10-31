#ifndef _3FENGINE_SRC_SCE_COMPONENTS_COMPONENTS_HPP_
#define _3FENGINE_SRC_SCE_COMPONENTS_COMPONENTS_HPP_

#include "utils/f_typedefs.hpp"

namespace fengine {
	class Position{
	public:
		Position() : pos_({ 0.0f, 0.0f, 0.0f }) {}
		~Position() = default;

		Position(const FPoint3f& point) : pos_(point) {}
		const FPoint3f& pos() const { return pos_; }
	private:
		FPoint3f pos_;
	};
}
#endif // _3FENGINE_SRC_SCE_COMPONENTS_COMPONENTS_HPP_