#ifndef _3FENGINE_SRC_FCOMPONENTS_F_EVENTS_MANAGER_HPP_
#define _3FENGINE_SRC_FCOMPONENTS_F_EVENTS_MANAGER_HPP_

#include <atomic>
#include <type_traits>

#include <utils/f_typedefs.hpp>
#include <utils/f_singleton.hpp>

#include <event_system/listeners/f_event_listener.hpp> 
#include <event_system/f_sdl_events_dispatcher.hpp>


namespace fengine
{
	class FEventsManager : FSdlEventsDispatcher, public futils::FSingleton<FEventsManager>
	{
		F_DISABLE_COPY(FEventsManager)
	public:
		FEventsManager() : last_id_(0) {}

		virtual ~FEventsManager()
		{
			std::cout << "FEventsManager dtro" << std::endl;
		}

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

		template<typename EventListener, typename EventType>
		void DelegateEvent(EventType&& event, fevents::EventSourceType source_type)
		{
			for (auto it = handlers_.begin(); it != handlers_.end() && !event.accepted(); ++it)
			{
				auto ptr = it->second.get();
				if (ptr->IsListenableSource(source_type))
				{
					static_cast<EventListener*>(it->second.get())->CallEvent(event);
				}
			}
		}

	private:
		std::atomic_int last_id_;
		FMap<int, FShared<FEventListener>> handlers_;

		constexpr static int kMaxLastId = 1024;
	};
}


#endif // _3FENGINE_SRC_FCOMPONENTS_F_EVENTS_MANAGER_HPP_