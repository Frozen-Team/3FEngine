#ifndef _3FENGINE_SRC_GUI_F_GUI_ENUMS_HPP_
#define _3FENGINE_SRC_GUI_F_GUI_ENUMS_HPP_

#include <utils/f_flags.hpp>

namespace fengine
{
	namespace fgui
	{
		enum WindowFlag
		{
			kWindowFullscreen	= 0x00000001,
			kWindowOpenGl		= 0x00000002,
			kWindowShown		= 0x00000004,
			kWindowHidden		= 0x00000008,
			kWindowBordless		= 0x00000010,
			kWindowResizeble	= 0x00000020,
			kWindowMinimized	= 0x00000040,
			kWindowMaximized	= 0x00000080,
			kWindowInputGrabbed	= 0x00000100,
			kWindowInputFocus	= 0x00000200,
			kWindowMouseFocus	= 0x00000400,
			kWindowFullDesktop	= (kWindowFullscreen | 0x00001000),
			kWindowFOREIGN		= 0x00000800,
			kWindowAllowHighDpi	= 0x00002000,
			kWindowMouseCapture	= 0x00004000
		};

		F_DECLARE_FLAGS_ENUM(WindowFlag, WindowFlags)

	}
}

#endif // _3FENGINE_SRC_GUI_F_GUI_ENUMS_HPP_