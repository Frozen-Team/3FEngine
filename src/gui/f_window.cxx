#include "f_window.hpp"

namespace fengine
{
	const FString FWindow::kDefaultTitle = "Default title";
	FWindow::FWindow()
		: id_(GetSdlWindowId()), active_(false), visible_(false), exposed_(false), close_requested_(false), title_(kDefaultTitle), pos_(0, 0), size_(kDefaultWidth, kDefaultHeight)
	{}

	FWindow::FWindow(const FString& title, const FPoint2i& pos, const FPoint2i& size, const fgui::WindowFlags& flags)
		: id_(0), active_(false), visible_(false), exposed_(false), close_requested_(false), pos_(pos), size_(size)
	{
		id_ = CreateSdlWindow(title, pos, size, flags);
	}

	void FWindow::Show()
	{
		
	}

	void FWindow::CallEvent(FWindowEvent& e)
	{
		if (e.which() == id_)
		{
			switch (e.type())
			{
			case fevents::kNoEvent: break;
			case fevents::kWindowClose:
				close_requested_ = true;
				break;
				// TODO: is exposed
			case fevents::kWindowExposed:
				exposed_ = true;
				break;
			case fevents::kWindowShown:
				visible_ = true;
				break;
			case fevents::kWindowHidden:
				visible_ = false;
				break;
			case fevents::kWindowMoved:
				pos_ = e.pos();
				break;
			case fevents::kWindowResized:
			case fevents::kWindowSizeChanged:
				size_ = e.size();
				break;
			case fevents::kWindowMinimized: break;
			case fevents::kWindowMaximized: break;
			case fevents::kWindowRestored: break;
			case fevents::kWindowFocusGained:
				active_ = true;
				break;
			case fevents::kWindowFocusLost:
				active_ = false;
				break;
			default: break;
			}
			FWindowListener::CallEvent(e);
		}
	}
}
