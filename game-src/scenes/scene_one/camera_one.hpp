#ifndef _GAME_SRC_SCENES_SCENE_ONE_CAMERA_ONE_HPP
#define _GAME_SRC_SCENES_SCENE_ONE_CAMERA_ONE_HPP

#include <scene/camera/f_camera.hpp>
#include <event_system/listeners/f_mouse_listener.hpp>
#include <event_system/listeners/f_keyboard_listener.hpp>

class CameraOne : public fengine::FCamera, public fengine::FMouseListener, public fengine::FKeyboardListener
{
protected:
	virtual void OnMouseButtonPressed(fengine::FMouseEvent& e) override;

	virtual void OnMouseButtonReleased(fengine::FMouseEvent& e) override;

	virtual void OnMouseMove(fengine::FMouseEvent& e) override;
public:
	CameraOne();

	virtual ~CameraOne() = default;
};

#endif // _GAME_SRC_SCENES_SCENE_ONE_CAMERA_ONE_HPP