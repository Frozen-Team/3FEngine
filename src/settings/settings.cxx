#include "settings.hpp"
#include "..\utils\utils.hpp"

#include <string>

namespace FEngine {

#define ADD_DEFAULT_SETTING(map_name,enum_name) {map_name[enum_name] = Utils::ToLower(#enum_name);}

	const Settings::DefaultSettingsMap Settings::default_settings_ = [] {
		Settings::DefaultSettingsMap ret_map;

		ADD_DEFAULT_SETTING(ret_map, WindowHeight);
		ADD_DEFAULT_SETTING(ret_map, WindowWidth);
		ADD_DEFAULT_SETTING(ret_map, WindowCaption);

		return ret_map;
	}();


	void Settings::LoadDefaultSettings()
	{
		Set<int>(SettingsNames::WindowWidth, 1024);
		Set<int>(SettingsNames::WindowHeight, 768);
		Set<std::string>(SettingsNames::WindowCaption, std::string("Sample window"));
	}
}