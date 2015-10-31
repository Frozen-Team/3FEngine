#ifndef _3FENGINE_SRC_EVENTS_F_EVENT_HPP_
#define _3FENGINE_SRC_EVENTS_F_EVENT_HPP_

class FEvent
{
public:
	enum EventType
	{
		kNoEvent,
		kKeyPress,
		kKeyRelease,
		kMouseMove,
		kMouseButtonDblClick,
		kMouseButtonPress,
		kMouseButtonRelease,
		kMouseWheel,
		kJoystick
	};

	explicit FEvent(EventType type) { this->type_ = type; }

	EventType type() const { return this->type_; }

	bool accepted() const { return this->accepted_; }

	void accept() { setAccepted(true); }

	void ignore() { setAccepted(false); }

	inline void setAccepted(bool accepted) { this->accepted_ = accepted; }

private:
	EventType type_;
	bool accepted_;
};

#endif // _3FENGINE_SRC_EVENTS_F_EVENT_HPP_