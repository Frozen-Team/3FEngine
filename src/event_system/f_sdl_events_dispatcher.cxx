#include "f_sdl_events_dispatcher.hpp"

#include "SDL_joystick.h"
#include "SDL_mouse.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include <helpers/f_sdl_helper.hpp>

namespace fengine
{
	FMap<unsigned, SDL_Joystick*> FSdlEventsDispatcher::joystick_handles_ = {};
	// TODO: Init structs with real values from SDL?
	F_STATIC_DECL_INIT(FSdlEventsDispatcher, jame_ )	= { 0, 0, 0 };
	F_STATIC_DECL_INIT(FSdlEventsDispatcher, jbme_ )	= { 0, 0,{ 0, 0 } };
	F_STATIC_DECL_INIT(FSdlEventsDispatcher, jbe_  )	= { fevents::kNoEvent, 0, 0 };
	F_STATIC_DECL_INIT(FSdlEventsDispatcher, jde_  )	= { fevents::kNoEvent, 0 };
	F_STATIC_DECL_INIT(FSdlEventsDispatcher, jhme_ )	= { 0, 0, 0 };
	F_STATIC_DECL_INIT(FSdlEventsDispatcher, ke_   )	= { fevents::kNoEvent, 0, fevents::KeyboardKey::kNoKey, fevents::KeyboardModifiers() };
	F_STATIC_DECL_INIT(FSdlEventsDispatcher, me_   )	= { fevents::kNoEvent, 0,{ 0, 0 }, fevents::MouseButton::kNoButton, fevents::MouseButtons(), fevents::KeyboardModifiers() };
	F_STATIC_DECL_INIT(FSdlEventsDispatcher, mwe_  )	= { { 0, 0 }, 0,{ 0, 0 }, fevents::MouseButtons(), fevents::KeyboardModifiers() };
	F_STATIC_DECL_INIT(FSdlEventsDispatcher, we_   )	= { fevents::kNoEvent, 0,{ 0, 0 },{ 0, 0 } };

	F_STATIC_DECL_INIT(FSdlEventsDispatcher, last_event_);
	F_STATIC_DECL_INIT(FSdlEventsDispatcher, event_);

	FSdlEventsDispatcher::FSdlEventsDispatcher()		
	{	
		SDL_AddEventWatch(JoystickDeviceEventsHandler, nullptr);
		SDL_SetEventFilter(UnusedEventsFilter, nullptr);

		auto num_joys = SDL_NumJoysticks();
		for (auto i = 0; i < num_joys; ++i)
		{
			OpenJoystick(i);
		}
	}

	FSdlEventsDispatcher::~FSdlEventsDispatcher()
	{
		for (auto& key : joystick_handles_)
		{
			CloseJoystick(key.first);
		}
	}

	int FSdlEventsDispatcher::JoystickDeviceEventsHandler(void* data, SDL_Event* event)
	{
		LOG_IF(event == nullptr, FATAL) << "Null event passed in handler.";
		switch (event->type)
		{
		case SDL_JOYDEVICEADDED:
		{
			auto which = event->jdevice.which;
			SDL_JoystickGetDeviceGUID(which);
			OpenJoystick(which);
			break;
		}
		case SDL_JOYDEVICEREMOVED:
		{
			auto joy_instance_id = event->jdevice.which;
			CloseJoystick(joy_instance_id);
		}
		}
		return 1;
	}

	int FSdlEventsDispatcher::UnusedEventsFilter(void* data, SDL_Event* event)
	{
		LOG_IF(event == nullptr, FATAL) << "Null event passed in handler.";
		auto ret_value = 1;
		switch (event->type)
		{
		case SDL_TEXTINPUT:
		case SDL_TEXTEDITING:
		case SDL_FINGERUP:
		case SDL_FINGERDOWN:
		case SDL_FINGERMOTION:
		case SDL_QUIT:
			ret_value = 0;
		}
		return ret_value;
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
		auto ret = SDL_PollEvent(&event_) != 0;
		if (ret)
		{
			if (event_.type == SDL_WINDOWEVENT)
			{
				last_event_.sdl_type = event_.type + event_.window.event + 1;
			} else
			{
				last_event_.sdl_type = event_.type;
			}
			switch (event_.type)
			{
			case SDL_MOUSEMOTION:
				me_.type = last_event_.type;
				me_.which = event_.motion.which;
				me_.button = fevents::kNoButton;
				me_.buttons.ResetFlags(SDL_GetMouseState(&me_.pos.x(), &me_.pos.y()));
				me_.modifiers.ResetFlags(SDL_GetModState());
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				me_.type = last_event_.type;
				me_.which = event_.button.which;
				me_.button = static_cast<fevents::MouseButton>(event_.button.button);
				me_.buttons.ResetFlags(SDL_GetMouseState(&me_.pos.x(), &me_.pos.y()));
				me_.modifiers.ResetFlags(event_.button.type);
				break;
			case SDL_MOUSEWHEEL:
				mwe_.which = event_.wheel.which;
				mwe_.delta.x() = event_.wheel.x;
				mwe_.delta.y() = event_.wheel.y;
				mwe_.buttons.ResetFlags(SDL_GetMouseState(&mwe_.pos.x(), &mwe_.pos.y()));
				mwe_.modifiers.ResetFlags(SDL_GetModState());
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				ke_.type = last_event_.type;
				ke_.which = 0;
				ke_.key = static_cast<fevents::KeyboardKey>(event_.key.keysym.scancode);
				ke_.modifiers.ResetFlags(SDL_GetModState());
				break;
			case SDL_JOYAXISMOTION:
				jame_.which = event_.jaxis.which;
				jame_.axis = event_.jaxis.axis;
				jame_.value = event_.jaxis.value;
				break;
			case SDL_JOYBALLMOTION:
				jame_.which = event_.jaxis.which;
				jame_.axis = event_.jaxis.axis;
				jame_.value = event_.jaxis.value;
				break;
			case SDL_JOYHATMOTION:
				jhme_.which = event_.jhat.which;
				jhme_.hat = event_.jhat.which;
				jhme_.value = event_.jhat.value;
				break;
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
				jbe_.type = last_event_.type;
				jbe_.which = event_.jbutton.which;
				jbe_.button = event_.jbutton.button;
				break;
			case SDL_JOYDEVICEADDED:
			case SDL_JOYDEVICEREMOVED:
				jde_.type = last_event_.type;
				jde_.which = event_.jdevice.which;
				break;
			case SDL_WINDOWEVENT:
			//case SDL_QUIT:
			{
				we_.type = last_event_.type;
				we_.which = event_.window.windowID;
				auto w = SDL_GetWindowFromID(event_.window.windowID);
				SDL_GetWindowPosition(w, &we_.pos.x(), &we_.pos.y());
				SDL_GetWindowSize(w, &we_.size.x(), &we_.size.y());
				break;
			}
			//case SDL_SYSWMEVENT:break;
			//case SDL_TEXTEDITING:break;
			//case SDL_TEXTINPUT:break;
			//case SDL_APP_TERMINATING: break;
			//case SDL_APP_LOWMEMORY: break;
			//case SDL_APP_WILLENTERBACKGROUND:break;
			//case SDL_APP_DIDENTERBACKGROUND:break;
			//case SDL_APP_WILLENTERFOREGROUND:break;
			//case SDL_APP_DIDENTERFOREGROUND:break;
			//case SDL_FIRSTEVENT: break;
			//case SDL_CONTROLLERAXISMOTION:break;
			//case SDL_CONTROLLERBUTTONDOWN:break;
			//case SDL_CONTROLLERBUTTONUP:break;
			//case SDL_CONTROLLERDEVICEADDED:break;
			//case SDL_CONTROLLERDEVICEREMOVED:break;
			//case SDL_CONTROLLERDEVICEREMAPPED:break;
			//case SDL_FINGERDOWN:break;
			//case SDL_FINGERUP:break;
			//case SDL_FINGERMOTION:break;
			//case SDL_DOLLARGESTURE:break;
			//case SDL_DOLLARRECORD:break;
			//case SDL_MULTIGESTURE:break;
			//case SDL_CLIPBOARDUPDATE:break;
			//case SDL_DROPFILE:break;
			//case SDL_AUDIODEVICEADDED:break;
			//case SDL_AUDIODEVICEREMOVED:break;
			//case SDL_RENDER_TARGETS_RESET:break;
			//case SDL_RENDER_DEVICE_RESET:break;
			default: break;
			}
		}
		return ret;
	}
	fevents::KeyboardModifiers FSdlEventsDispatcher::GetKeyboardModifiers() noexcept
	{
		return fevents::KeyboardModifiers(SDL_GetModState());
	}
}
