#ifndef _3FENGINE_SRC_F_MAIN_LOOP_INTERFACE_HPP_
#define _3FENGINE_SRC_F_MAIN_LOOP_INTERFACE_HPP_

//#include <engine.hpp>

namespace fengine
{
	class FMainLoopInterface
	{
		friend class Engine;
	public:
		virtual ~FMainLoopInterface() = default;

		bool is_running() const noexcept { return running_; }

		void Terminate() { running_ = false; }

	protected:
		explicit FMainLoopInterface(bool running = true) : running_(running) {}

		virtual void OnInit() = 0;

		virtual void OnPreUpdate() = 0;

		virtual void OnPostUpdate() = 0;

		virtual int OnTerminate() = 0;

	private:
		bool running_;
	};
}

#endif // _3FENGINE_SRC_F_MAIN_LOOP_INTERFACE_HPP_