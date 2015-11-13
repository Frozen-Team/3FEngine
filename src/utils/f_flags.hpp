#ifndef _3FENGINE_SRC_UTILS_F_FLAGS_HPP_
#define _3FENGINE_SRC_UTILS_F_FLAGS_HPP_

#include <type_traits>

#include <fcomponents/f_logger.hpp>

namespace fengine
{
	template<typename EnumType, typename Enable = void>
	class FFlags {};

	template<typename EnumType>
	class FFlags<EnumType, typename std::enable_if<std::is_enum<EnumType>::value>::type>
	{
		using FlagType = typename std::underlying_type<EnumType>::type;
	public:

		FFlags() : flags_(0) {}

		explicit FFlags(FlagType flags) { this->flags_ = flags; }

		explicit FFlags(EnumType flag)
		{
			FlagType f = static_cast<FlagType>(flag);
			LOG_IF(((f & (f - 1)) != 0) && (f != 0), WARNING) << "Passed flag is not a power of 2. Value: " << f;
			this->flags_ = static_cast<FlagType>(flag);
		}

		FlagType ToNumber() const { return static_cast<FlagType>(this->flags_); }

		bool IsSet(const EnumType flag) const { return (static_cast<FlagType>(flag) & this->flags_) != 0; }

		void Reset() const noexcept { this->flags_ = static_cast<FlagType>(0); }

		void Reset(FlagType value) noexcept { this->flags_ = value; }

	public:
		FFlags& operator=(EnumType rhs) noexcept
		{
			this->flags_ = static_cast<FlagType>(rhs);
			return *this;
		}
		friend FFlags operator~(const FFlags& v) noexcept
		{
			return FFlags(~v.flags_);
		}
		friend FFlags operator|(const FFlags& lhs, const FFlags& rhs) noexcept
		{
			return FFlags(lhs.flags_ | rhs.flags_);
		}
		friend FFlags operator&(const FFlags& lhs, const FFlags& rhs) noexcept
		{
			return FFlags(lhs.flags_ & rhs.flags_);
		}
		friend FFlags operator^(const FFlags& lhs, const FFlags& rhs) noexcept
		{
			return FFlags(lhs.flags_ ^ rhs.flags_);
		}
		friend FFlags& operator|=(FFlags& lhs, const FFlags& rhs) noexcept
		{
			lhs.flags_ |= rhs.flags_;
			return lhs;
		}
		friend FFlags& operator&=(FFlags& lhs, FFlags rhs) noexcept
		{
			lhs.flags_ &= rhs.flags_;
			return lhs;
		}
		friend FFlags& operator^=(FFlags& lhs, FFlags rhs) noexcept
		{
			lhs.flags_ ^= rhs.flags_;
			return lhs;
		}

	private:
		FlagType flags_;
	};

#define F_DECLARE_FLAGS_ENUM(EnumName,FlagsName) using FlagsName = FFlags<EnumName>;

}

#endif // _3FENGINE_SRC_UTILS_F_FLAGS_HPP_