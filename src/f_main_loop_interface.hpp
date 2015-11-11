#ifndef _3FENGINE_SRC_F_MAIN_LOOP_INTERFACE_HPP_
#define _3FENGINE_SRC_F_MAIN_LOOP_INTERFACE_HPP_

//#include <engine.hpp>

namespace fengine
{
	class FMainLoopInterface
	{
	public:
		virtual ~FMainLoopInterface() = default;

		bool running() const noexcept { return running_; }

		int Run();

		void Terminate() { running_ = false; }

	protected:
		explicit FMainLoopInterface(bool running = true) : running_(running) {}

		friend class Engine;

		virtual void OnInit() = 0;

		virtual int Exec() = 0;

	private:
		bool running_;
	};
}

#endif // _3FENGINE_SRC_F_MAIN_LOOP_INTERFACE_HPP_