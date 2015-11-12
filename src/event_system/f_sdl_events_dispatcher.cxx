#include "f_sdl_events_dispatcher.hpp"

#include "SDL_joystick.h"
#include "SDL_mouse.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include <helpers/f_sdl_helper.hpp>

namespace fengine
{
//	struct
//	{
//		fevents::EventType type;
//		unsigned which;
//		FPoint2i pos;
//		fevents::MouseButton button;
//		fevents::MouseButtons buttons;
//		fevents::KeyboardModifiers modifiers;
//	} me_; // FMouseEvent
//
//	struct
//	{
//		int delta;
//		unsigned which;
//		FPoint2i position;
//		fevents::MouseButtons buttons;
//		fevents::KeyboardModifiers modifiers;
//		fevents::WheelOrientation orientation;
//	} mwe_; // FMouseWheelEvent

	FSdlEventsDispatcher::FSdlEventsDispatcher() :
		jame_({ 0, 0, 0 }), 
		jbme_({ 0, 0,{ 0, 0 } }),
		jbe_({ fevents::kNoEvent, 0, 0 }),
		jde_({ fevents::kNoEvent, 0 }),
		jhme_({ 0, 0, 0 }),
		// TODO:
		//ke_({ fevents::kNoEvent, 0, 0, 0 }),
		//me_
		//mwe_
		we_({ fevents::kNoEvent, 0, {0, 0}, {0, 0}}),
		mouse_wheel_delta_(0)
	{
		auto num_joys = SDL_NumJoysticks();
		SDL_AddEventWatch(JoystickDeviceEventsHandler, nullptr);

		for (auto i = 0; i < num_joys; ++i)
		{
			OpenJoystick(i);
		}
	}

	FSdlEventsDispatcher::~FSdlEventsDispatcher()
	{
		// TODO: Close opened joysticks
	}

	FMap<unsigned, SDL_Joystick*> FSdlEventsDispatcher::joystick_handles_ = {};
	int FSdlEventsDispatcher::JoystickDeviceEventsHandler(void* data, SDL_Event* event)
	{
		auto ret_value = 1;
		switch (event->type)
		{
		case SDL_JOYDEVICEADDED:
		{
			auto which = event->jdevice.which;
			SDL_JoystickGetDeviceGUID(which);
			OpenJoystick(which);
			ret_value = 0;
			break;
		}
		case SDL_JOYDEVICEREMOVED:
		{
			auto joy_instance_id = event->jdevice.which;
			CloseJoystick(joy_instance_id);
			ret_value = 0;
		}
		}
		return 1;
	}

	void FSdlEventsDispatcher::OpenJoystick(unsigned which)
	{
		auto p_joystick = SDL_JoystickOpen(which);
		LOG_IF(p_joystick == nullptr, FATAL) << "Cannot open joystick. Which: " << which;
		auto joy_instance_id = SDL_JoystickInstanceID(p_joystick);
		LOG_IF(joy_instance_id < 0, FATAL) << "Cannot retrieve joystick ID. Which : " << which << ". Error: " << (FSdlHelper::CheckError() ? FSdlHelper::GetLastError() : "");
		joystick_handles_[joy_instance_id] = p_joystick;
		LOG(INFO) << "Joystick added. ID: " << joy_instance_id;
	}

	void FSdlEventsDispatcher::CloseJoystick(unsigned joy_instance_id)
	{
		auto it = joystick_handles_.find(joy_instance_id);
		if (it != joystick_handles_.end())
		{
			if (SDL_JoystickGetAttached(it->second))
			{
				SDL_JoystickClose(it->second);
				LOG(INFO) << "Joystick closed. ID: " << joy_instance_id;
			}		
			joystick_handles_.erase(it);		
		} else
		{
			LOG(WARNING) << "Joystick not found. ID: " << joy_instance_id;
		}
	}

	FString FSdlEventsDispatcher::GetJoystickGuid(unsigned which)
	{
		auto guid = SDL_JoystickGetDeviceGUID(which);
		auto guid_str = reinterpret_cast<const char*>(&guid.data[0]);
		return FString(guid_str, 16);
	}

	bool FSdlEventsDispatcher::PollEvent()
	{
		auto ret = SDL_PollEvent(&this->event_) != 0;
		if (ret)
		{
			// Ignore some events
			if (event_.type == SDL_FINGERMOTION || event_.type == SDL_FINGERDOWN || event_.type == SDL_FINGERUP || event_.type == SDL_TEXTINPUT || event_.type == SDL_TEXTEDITING)
			{
				event_type_union_.sdl_type = 0;
			}
			else 
			{
				if (event_.type == SDL_WINDOWEVENT)
				{
					event_type_union_.sdl_type = event_.type + event_.window.event + 1;
				} else
				{
					event_type_union_.sdl_type = event_.type;
				}
				
			}
			switch (event_.type)
			{
			case SDL_FIRSTEVENT: break;
			case SDL_QUIT: break;

			case SDL_APP_TERMINATING: break;
			case SDL_APP_LOWMEMORY: break;
			case SDL_APP_WILLENTERBACKGROUND:break;
			case SDL_APP_DIDENTERBACKGROUND:break;
			case SDL_APP_WILLENTERFOREGROUND:break;
			case SDL_APP_DIDENTERFOREGROUND:break;

			case SDL_WINDOWEVENT:break;
			case SDL_SYSWMEVENT:break;

			case SDL_KEYDOWN:break;
			case SDL_KEYUP:break;
			case SDL_TEXTEDITING:break;
			case SDL_TEXTINPUT:break;

			case SDL_MOUSEMOTION:break;
			case SDL_MOUSEBUTTONDOWN:break;
			case SDL_MOUSEBUTTONUP:break;

			case SDL_MOUSEWHEEL:break;

			case SDL_JOYAXISMOTION:break;

			case SDL_JOYBALLMOTION:break;

			case SDL_JOYHATMOTION:break;

			case SDL_JOYBUTTONDOWN:break;
			case SDL_JOYBUTTONUP:break;

			case SDL_JOYDEVICEADDED:
				break;
			case SDL_JOYDEVICEREMOVED:
				break;

			case SDL_CONTROLLERAXISMOTION:break;
			case SDL_CONTROLLERBUTTONDOWN:break;
			case SDL_CONTROLLERBUTTONUP:break;
			case SDL_CONTROLLERDEVICEADDED:break;
			case SDL_CONTROLLERDEVICEREMOVED:break;
			case SDL_CONTROLLERDEVICEREMAPPED:break;

			case SDL_FINGERDOWN:break;
			case SDL_FINGERUP:break;
			case SDL_FINGERMOTION:break;
			case SDL_DOLLARGESTURE:break;
			case SDL_DOLLARRECORD:break;
			case SDL_MULTIGESTURE:break;
			case SDL_CLIPBOARDUPDATE:break;
			case SDL_DROPFILE:break;
			case SDL_AUDIODEVICEADDED:break;
			case SDL_AUDIODEVICEREMOVED:break;
			case SDL_RENDER_TARGETS_RESET:break;
			case SDL_RENDER_DEVICE_RESET:break;
			default: break;
			}
			switch (event_.type)
			{
			case SDL_MOUSEWHEEL:
				mouse_wheel_delta_ = event_.wheel.direction;
				break;
			}
		}
		return ret;
	}
	fevents::KeyboardModifiers FSdlEventsDispatcher::GetKeyboardModifiers() const noexcept
	{
		return fevents::KeyboardModifiers(event_.key.keysym.mod);
	}
}
