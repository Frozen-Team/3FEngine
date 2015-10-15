#include "f_settings.hpp"
#include "..\utils\f_utils.hpp"

#include <string>

namespace fengine {

#define ADD_DEFAULT_SETTING(map_name,enum_name) {map_name[enum_name] = futils::ToLower(#enum_name);}

	const FSettings::DefaultSettingsMap FSettings::default_settings_ = [] {
		FSettings::DefaultSettingsMap ret_map;

		ADD_DEFAULT_SETTING(ret_map, WindowHeight);
		ADD_DEFAULT_SETTING(ret_map, WindowWidth);
		ADD_DEFAULT_SETTING(ret_map, WindowCaption);

		return ret_map;
	}();


	void FSettings::LoadDefaultSettings()
	{
		Set<int>(SettingsNames::WindowWidth, 1024);
		Set<int>(SettingsNames::WindowHeight, 768);
		Set<std::string>(SettingsNames::WindowCaption, std::string("Sample window"));
	}
}