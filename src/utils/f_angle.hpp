#ifndef _3FENGINE_SRC_UTILS_F_ANGLE_HPP_
#define _3FENGINE_SRC_UTILS_F_ANGLE_HPP_

#include "f_utils.hpp"
namespace fengine
{
	class FAngle
	{
	public:
		FAngle() : radians_(0.0f) {}
		~FAngle() = default;

		explicit FAngle(float radians) : radians_(radians) {}

		static FAngle Radians(float radians)
		{
			return FAngle(radians);
		}

		static FAngle Degrees(float degrees)
		{
			return FAngle(futils::DegreesToRadians(degrees));
		}

		float radians() const { return radians_; }
	private:
		float radians_;
	};
}
#endif // _3FENGINE_SRC_UTILS_F_ANGLE_HPP_