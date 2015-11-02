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

		int Register(FUnique<FEventListener> handler);

		int Deregister(int id);

		void HandleEvents();

	private:
		//template<typename ListenerType, typename EventType>
		//inline ListenerType& DelegateEvent(EventType type, EventSourceType source_type, EventType event)
		//{
		//	for (auto& it = handlers_.begin(); it != handlers_.end(); it++)
		//	{
		//		auto ptr = it->second.get();
		//		if (ptr->source_types().IsSet(source_type))
		//		{
		//			static_cast<ListenerType*>(it->second.get())->OnKeyReleased(keyboardEvent);
		//		}
		//	}
		//}

		//template<typename T>
		//void Exec(EventType type)
		//{
		//	auto 
		//}

		int GetNewEventId();
	

	private:
		std::atomic_int last_id_;
		FMap<int, FUnique<FEventListener>> handlers_;

		constexpr static int kMaxLastId = 1024;
	};
}


#endif // _3FENGINE_SRC_FCOMPONENTS_F_EVENTS_MANAGER_HPP_