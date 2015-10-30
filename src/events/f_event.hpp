#ifndef _3FENGINE_SRC_EVENTS_F_EVENT_HPP_
#define _3FENGINE_SRC_EVENTS_F_EVENT_HPP_

class FEvent
{
public:
	enum Type
	{
		KeyPress,
		KeyRelease,
		MouseMove,
		MouseButtonDblClick,
		MouseButtonPress,
		MouseButtonRelease,
		MouseWheel,
		Joystick
	};

	explicit FEvent(Type type) { this->type_ = type; }

	Type type() const { return this->type_; }

	bool accepted() const { return this->accepted_; }

	void accept() { setAccepted(true); }

	void ignore() { setAccepted(false); }

	inline void setAccepted(bool accepted) { this->accepted_ = accepted; }

private:
	Type type_;
	bool accepted_;
};

#endif // _3FENGINE_SRC_EVENTS_F_EVENT_HPP_