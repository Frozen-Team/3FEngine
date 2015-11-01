#ifndef _3FENGINE_SRC_EVENTS_LISTENERS_F_MOUSE_LISTENER_HPP_
#define _3FENGINE_SRC_EVENTS_LISTENERS_F_MOUSE_LISTENER_HPP_

#include <utils/f_typedefs.hpp>
#include <events/f_mouse_event.hpp>

namespace fengine
{
	class FMouseListener
	{
	public:
		FMouseListener() = default;

		virtual ~FMouseListener() = default;

	protected:
		virtual void OnMouseMove(const FMouseEvent& e) {}

		virtual void OnMouseButtonPressed(const FMouseEvent& e) {}

		virtual void OnMouseButtonReleased(const FMouseEvent& e) {}
	};
}

#endif // _3FENGINE_SRC_EVENTS_LISTENERS_F_MOUSE_LISTENER_HPP_