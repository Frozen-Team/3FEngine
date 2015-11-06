#ifndef _3FENGINE_SRC_FCOMPONENTS_F_EVENTS_MANAGER_HPP_
#define _3FENGINE_SRC_FCOMPONENTS_F_EVENTS_MANAGER_HPP_

#include <atomic>
#include <type_traits>

#include <utils/f_typedefs.hpp>
#include <utils/f_singleton.hpp>

#include <events/listeners/f_event_listener.hpp> 
#include <events/f_sdl_events_dispatcher.hpp>


namespace fengine
{
	class FEventsManager : public futils::FSingleton<FEventsManager>, FSdlEventsDispatcher
	{
		F_DISABLE_COPY(FEventsManager)
	public:
		FEventsManager() : last_id_(0) {}

		template<typename EventHandler>
		int Register()
		{
			static_assert(std::is_base_of<FEventListener, EventHandler>::value, "Not a derived class from FEventListener");
			auto new_id = GetNewEventId();
			handlers_[new_id] = std::make_shared<EventHandler>();
			return new_id;
		}

		template<typename EventHandler>
		int Register(FShared<EventHandler> handler)
		{
			auto new_id = GetNewEventId();
			handlers_[new_id] = std::move(handler);
			return new_id;
		}

		int Deregister(int id);

		void HandleEvents();

	private:

		int GetNewEventId();

	private:
		std::atomic_int last_id_;
		FMap<int, FShared<FEventListener>> handlers_;

		constexpr static int kMaxLastId = 1024;
	};
}


#endif // _3FENGINE_SRC_FCOMPONENTS_F_EVENTS_MANAGER_HPP_