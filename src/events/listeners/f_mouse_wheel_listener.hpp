#ifndef _3FENGINE_SRC_EVENTS_LISTENERS_F_MOUSE_WHEEL_LISTENER_HPP_
#define _3FENGINE_SRC_EVENTS_LISTENERS_F_MOUSE_WHEEL_LISTENER_HPP_

#include <utils/f_typedefs.hpp>
#include <events/f_mouse_wheel_event.hpp>

namespace fengine
{
	class FMouseWheelListener
	{
	public:
		FMouseWheelListener() = default;

		virtual ~FMouseWheelListener() = default;

	protected:
		virtual void OnMouseWheelScrolled(const FMouseWheelEvent& e) {}
	};
}

#endif // _3FENGINE_SRC_EVENTS_LISTENERS_F_MOUSE_WHEEL_LISTENER_HPP_