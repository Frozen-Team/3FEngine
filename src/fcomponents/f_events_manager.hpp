#ifndef _3FENGINE_SRC_FCOMPONENTS_F_EVENTS_MANAGER_HPP_
#define _3FENGINE_SRC_FCOMPONENTS_F_EVENTS_MANAGER_HPP_

#include <atomic>

#include <utils/f_typedefs.hpp>
#include <utils/f_singleton.hpp>
#include <events/f_sdl_events_dispatcher.hpp>

#include <events/listeners/f_keyboard_listener.hpp>
#include <events/listeners/f_mouse_listener.hpp>
#include <events/listeners/f_mouse_wheel_listener.hpp>

namespace fengine
{
	class FEventsManager : public futils::FSingleton<FEventsManager>, FSdlEventsDispather
	{
		F_DISABLE_COPY(FEventsManager)

	public:
		FEventsManager() {}

		static int RegisterEventHandler(FUnique<FKeyboardListener> handler);

		static int RegisterEventHandler(FUnique<FMouseListener> handler);
		
		static int RegisterEventHandler(FUnique<FMouseWheelListener> handler);

	private:
		static int GetNewEventId();

	private:
		static std::atomic_int last_id_;
		static FMap<int, FUnique<FKeyboardListener>> keyboard_handlers_;
		static FMap<int, FUnique<FMouseListener>> mouse_handlers_;
		static FMap<int, FUnique<FMouseWheelListener>> mouse_wheel_handlers_;

		constexpr static int kMaxLastId = 100000;

	};
}


#endif // _3FENGINE_SRC_FCOMPONENTS_F_EVENTS_MANAGER_HPP_