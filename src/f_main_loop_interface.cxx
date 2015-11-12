#include "f_main_loop_interface.hpp"

namespace fengine
{
	int FMainLoopInterface::Run()
	{
		running_ = true;
		return Exec();
	}
}
