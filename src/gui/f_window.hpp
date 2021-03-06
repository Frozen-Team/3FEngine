#ifndef _3FENGINE_SRC_GUI_F_WINDOW_HPP_
#define _3FENGINE_SRC_GUI_F_WINDOW_HPP_

#include <utils/f_typedefs.hpp>
#include <event_system/listeners/f_window_listener.hpp>
#include "f_sdl_window.hpp"

namespace fengine
{
	class FWindow : public FWindowListener, public FSdlWindow
	{
		const static FString kDefaultTitle;
		enum
		{
			kDefaultWidth = 200,
			kDefaultHeight = 200
		};	
	public:
		FWindow();

		explicit FWindow(const FString& title, const FPoint2i& pos, const FPoint2i& size, const fgui::WindowFlags& flags);

		virtual ~FWindow() = default;

		void Show();

		unsigned id() const noexcept { return id_; }

		bool active() const noexcept { return active_; }

		const FString& title() const noexcept { return title_; }
		
		const FPoint2i& pos() const noexcept { return pos_; }

		const FPoint2i& size() const noexcept { return size_; }

		const fgui::WindowFlags& flags() const noexcept { return GetSdlWindowFlags(); }

		bool IsCloseRequested() const
		{
			bool close = close_requested_;
			return close_requested_;
		}

	protected:
		virtual void CallEvent(FWindowEvent& e) override;

	private:
		unsigned id_;
		bool active_;
		bool visible_;
		bool exposed_;
		bool close_requested_;
		FString title_;
		FPoint2i pos_;
		FPoint2i size_;
		fgui::WindowFlags flags_;
	};
}
#endif // _3FENGINE_SRC_GUI_F_WINDOW_HPP_