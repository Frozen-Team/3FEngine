#ifndef _3FENGINE_SRC_UTILS_F_FLAGS_HPP_
#define _3FENGINE_SRC_UTILS_F_FLAGS_HPP_

#include <type_traits>

#include <components/f_logger.hpp>

template<typename EnumType>
using EnableIfPolicy = typename std::enable_if<std::is_enum<EnumType>::value, EnumType>::type;

template<typename EnumType, typename Enable = void>
class FFlags;

template<typename EnumType>
class FFlags<EnumType, typename std::enable_if<std::is_enum<EnumType>::value >::type>
{
	using FlagType = typename std::underlying_type<EnumType>::type;
public:
	FFlags(FlagType flags) { this->flags_ = flags; }

	FFlags() : flags_(0) {}

	FFlags(EnumType flag)
	{
		FlagType f = (FlagType)flag;
		LOG_IF(((f & (f - 1)) != 0) && (f != 0), WARNING) << "Passed flag is not a power of 2. Value: " << f;
		this->flags_ = (FlagType)flag;
	}

	FFlags(const EnumType& flag)
	{
		FlagType f = (FlagType)flag;
		LOG_IF(((f & (f - 1)) != 0) && (f != 0), WARNING) << "Passed flag is not a power of 2. Value: " << f;
		this->flags_ = (FlagType)flag;
	}

	FlagType ToNumber() const { return (FlagType)this->flags_; }

	bool IsSet(EnumType flag) { return (((FlagType)flag) & this->flags_) != 0; }

public:
	friend inline FFlags operator~(const FFlags& v)
	{
		return FFlags(~v.flags_);
	}
	friend inline FFlags operator|(const FFlags& lhs, const FFlags& rhs)
	{
		return FFlags(lhs.flags_ | rhs.flags_);
	}
	friend inline FFlags operator&(const FFlags& lhs, const FFlags& rhs)
	{
		return FFlags(lhs.flags_ & rhs.flags_);
	}
	friend inline FFlags operator^(const FFlags& lhs, const FFlags& rhs)
	{
		return FFlags(lhs.flags_ ^ rhs.flags_);
	}
	friend inline FFlags& operator|=(const FFlags& lhs, const FFlags& rhs)
	{
		lhs.flags_ |= rhs.flags_;
		return lhs;
	}
	friend inline FFlags& operator&=(FFlags& lhs, FFlags rhs)
	{
		lhs.flags_ &= rhs.flags_;
		return lhs;
	}
	friend inline FFlags& operator^=(FFlags& lhs, FFlags rhs)
	{
		lhs.flags_ ^= rhs.flags_;
		return lhs;
	}

private:
	FlagType flags_;
};

#endif // _3FENGINE_SRC_UTILS_F_FLAGS_HPP_