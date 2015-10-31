#include "f_time.hpp"

namespace fengine
{
	FTime::FTime(const FString & time_date)
	{
		SetTime(time_date);
	}

	FTime::FTime(time_t time)
	{
		SetTime(time);
	}

	void FTime::SetTime(time_t time)
	{
		this->time_ = boost::posix_time::from_time_t(time);
	}

	void FTime::SetTime(const FString & time_str)
	{
		this->time_ = boost::posix_time::time_from_string(time_str);
	}

	FString FTime::ToString()
	{
		return FString(boost::posix_time::to_simple_string(this->time_));
	}
	time_t FTime::ToTimestamp()
	{
		return boost::posix_time::to_time_t(this->time_);
	}
}