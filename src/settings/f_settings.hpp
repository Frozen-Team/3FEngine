#ifndef _3FENGINE_SRC_SETTINGS_F_SETTINGS_HPP_
#define _3FENGINE_SRC_SETTINGS_F_SETTINGS_HPP_

#include <map>
#include <memory>
#include <typeinfo>
#include <algorithm>
#include <string>
#include <assert.h>
#include <iostream>
#include <type_traits>

#include "..\utils\f_utils.hpp"

namespace fengine {

	class FSettingInterface
	{
	public:
		virtual ~FSettingInterface() {};
	};

	template<typename T>
	class FSettingField : public FSettingInterface
	{

	public:
		
		FSettingField() : t_(typeid(T)) {}
		FSettingField(const T& value) : t_(typeid(T)) { set_value(value); }
		FSettingField(const FSettingField& ref) : t_(ref.t_), value_(ref.value_) {}
		~FSettingField() {};

		const T& value() {
			CheckTypes();
			return this->value_;
		}
		void set_value(const T& v) {
			CheckTypes();
			this->value_ = v;
		}
	private:
		void CheckTypes() {
			auto a = typeid(T) == t_;
			if (!a) {
				std::cout << "Incompatible types: holds(" << typeid(T).name() << ") and requests(" << t_.name() << ")." << std::endl;
			}
			assert(a);
		}
		const std::type_info& t_;
		T value_;
	};

	class FSettings
	{
	public:
		FSettings() {}

		virtual ~FSettings() {}

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
				return futils::ToLower(t);
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
		void Set(T setting, FSettingField<V> value) noexcept {
			values_[futils::ToLower(SettingTraits<T>::setting(setting))] = std::make_unique<FSettingField<V>>(value);
		}

		template<typename V, typename T>
		const V& Get(T setting) {
			auto s = SettingTraits<T>::setting(setting);
			auto &found = values_.find(s);
			assert(found != values_.end());
			return static_cast<FSettingField<V>*>(found->second.get())->value();
		}

	private:
		std::map<std::string, std::unique_ptr<FSettingInterface>> values_;
		static const DefaultSettingsMap default_settings_;
	};
}

#endif // _3FENGINE_SRC_SETTINGS_F_SETTINGS_HPP_