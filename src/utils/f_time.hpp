#ifndef _3FENGINE_SRC_EVENTS_F_TIMESTAMP_HPP_
#define _3FENGINE_SRC_EVENTS_F_TIMESTAMP_HPP_

#include <ctime>
#include <boost/date_time.hpp>
#include <utils/f_typedefs.hpp>

namespace fengine
{
	class FTime
	{
	public:
		FTime() : time_(boost::posix_time::from_time_t(0)) {}

		FTime(const FString& time_str);

		FTime(time_t time);

		void SetTime(time_t time);

		void SetTime(const FString& time_str);

		FString ToString();

		time_t ToTimestamp();

	private:
		boost::posix_time::ptime time_;
	};
}
#endif // _3FENGINE_SRC_EVENTS_F_TIMESTAMP_HPP_