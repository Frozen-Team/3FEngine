#pragma once
#include <map>
#include <memory>
#include <typeinfo>
#include <algorithm>
#include <string>
#include <assert.h>
#include <iostream>

#include <type_traits>


#include "..\utils\utils.hpp"

namespace FEngine {

	class SettingInterface
	{
	public:
		virtual ~SettingInterface() {};
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

		virtual void LoadDefaultSettings();

		 enum SettingsNames {
			WindowHeight,
			WindowWidth,
			WindowCaption
		};


		using DefaultSettingsMap = std::map<SettingsNames, std::string>;

		template<typename T>
		struct SettingTraits {
			static std::string setting(T t) {
				return Utils::ToLower(t);
			}
		};

		template<>
		struct SettingTraits<SettingsNames> {
			static std::string setting(SettingsNames s) {
				auto &found = default_settings_.find(s);
				assert(found != default_settings_.end());
				return found->second;
			}
		};

		template<typename V, typename T>
		void Set(T setting, SettingField<V> value) noexcept {
			values_[Utils::ToLower(SettingTraits<T>::setting(setting))] = std::make_unique<SettingField<V>>(value);
		}

		template<typename V, typename T>
		const V& Get(T setting) {
			auto s = SettingTraits<T>::setting(setting);
			auto &found = values_.find(s);
			assert(found != values_.end());
			return static_cast<SettingField<V>*>(found->second.get())->value();
		}

	private:
		std::map<std::string, std::unique_ptr<SettingInterface>> values_;
		static const DefaultSettingsMap default_settings_;
	};
}