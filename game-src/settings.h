#pragma once
#include <map>
#include <memory>
#include <typeinfo>
#include <algorithm>
#include <string>
#include <assert.h>
#include <iostream>

#include <type_traits>


#include "utils.h"

namespace FEngine {

	class SettingInterface
	{
		~SettingInterface() = default;
	};

	template<typename T>
	class SettingField : public SettingInterface
	{

	public:
		
		SettingField() : t_(typeid(T)) {}
		SettingField(const T& value) : t_(typeid(T)) { set_value(value); }
		SettingField(const SettingField& ref) : t_(ref.t_), value_(ref.value_) {}
		~SettingField() {};

		const T& value() {
			check_types();
			return this->value_;
		}
		void set_value(const T& v) {
			check_types();
			this->value_ = v;
		}
	private:
		void check_types() {
			auto a = typeid(T) == t_;
			if (!a) {
				std::cout << "Incompatible types: holds(" << typeid(T).name() << ") and requests(" << t_.name() << ")." << std::endl;
			}
			assert(a);
		}
		const std::type_info& t_;
		T value_;
	};

	class Settings
	{
	public:
		Settings() {}

		virtual ~Settings() {}

		 enum SettingsNames {
			WindowHeight,
			WindowWidth,
			WindowCaption
		};


		using DefaultSettingsMap = std::map<SettingsNames, std::string>;

		virtual void LoadDefaultSettings();

		template<typename T>
		struct SettingTraits {
			static T setting(T t) {
				return t;
			}
		};

		template<>
		struct SettingTraits<SettingsNames> {
			static std::string setting(SettingsNames t) {
				return default_settings_.at(t);
			}
		};

		template<typename V, typename T>
		void Set(T t, SettingField<V> value) noexcept {
			values_[Utils::ToLower(SettingTraits<T>::setting(t))] = std::make_unique<SettingField<V>>(value);
		}

		template<typename T>
		const T& Get(const std::string setting_name) {
			auto &lower_case = Utils::ToLower(setting_name);
			auto &found = values_.find(lower_case);
			assert(found != values_.end());
			return static_cast<SettingField<T>*>(values_[lower_case].get())->value();
		}

		template<typename T>
		const T& Get(SettingsNames setting) {
			return Get<T>(GetSetting(setting));
		}

	private:
		std::string GetSetting(SettingsNames setting);

	private:
		std::map<std::string, std::unique_ptr<SettingInterface>> values_;
		static const DefaultSettingsMap default_settings_;
	};
}