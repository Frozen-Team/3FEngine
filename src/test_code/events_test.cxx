#include <iostream>
#include <event_system/listeners/f_keyboard_listener.hpp>
#include <event_system/listeners/f_mouse_listener.hpp>
#include <event_system/listeners/f_window_listener.hpp>


class KeyboardEventsHandler : public fengine::FKeyboardListener
{
public:
	virtual ~KeyboardEventsHandler() { std::cout << "dtor" << std::endl; }
protected:
	virtual void OnKeyPressed(fengine::FKeyboardEvent& e) override
	{
		std::cout << "OnKeyPressed() Key:" << e.key() << std::endl;
	}

	virtual void OnKeyReleased(fengine::FKeyboardEvent& e) override
	{
		std::cout << "OnKeyReleased() Key:" << e.key() << std::endl;
	}
};

class MouseEventListener : public fengine::FMouseListener
{
protected:
	virtual void OnMouseMove(fengine::FMouseEvent& e) override
	{
		std::cout << "OnMouseMove() Pos:" << e.pos().x() << std::endl;
	}

	virtual void OnMouseButtonPressed(fengine::FMouseEvent& e) override
	{
		std::cout << "OnMouseButtonPressed() Pos:" << e.pos().x() << ", " << e.pos().y() << std::endl;
	}

	virtual void OnMouseButtonReleased(fengine::FMouseEvent& e) override
	{
		std::cout << "OnMouseButtonReleased() Pos:" << e.pos().x() << ", " << e.pos().y() << std::endl;
	}
};

class WindowEventListener : public fengine::FWindowListener
{
protected:
	void OnWindowShown(fengine::FWindowEvent& e) override
	{
		std::cout << "OnWindowShown()" << std::endl;
	}
	void OnWindowHidden(fengine::FWindowEvent& e) override
	{
		std::cout << "OnWindowHidden()" << std::endl;
	}
	void OnWindowExposed(fengine::FWindowEvent& e) override
	{
		std::cout << "OnWindowExposed()" << std::endl;
	}
	void OnWindowMoved(fengine::FWindowEvent& e) override
	{
		std::cout << "OnWindowMoved()" << std::endl;
	}
	void OnWindowResized(fengine::FWindowEvent& e) override
	{
		std::cout << "OnWindowResized()" << std::endl;
	}
	void OnWindowSizeChanged(fengine::FWindowEvent& e) override
	{
		std::cout << "OnWindowSizeChanged()" << std::endl;
	}
	void OnWindowMinimized(fengine::FWindowEvent& e) override
	{
		std::cout << "OnWindowMinimized()" << std::endl;
	}
	void OnWindowMaximized(fengine::FWindowEvent& e) override
	{
		std::cout << "OnWindowMaximized()" << std::endl;
	}
	void OnWindowRestored(fengine::FWindowEvent& e) override
	{
		std::cout << "OnWindowRestored()" << std::endl;
	}
	void OnWindowEnter(fengine::FWindowEvent& e) override
	{
		std::cout << "OnWindowEnter()" << std::endl;
	}
	void OnWindowLeave(fengine::FWindowEvent& e) override
	{
		std::cout << "OnWindowLeave()" << std::endl;
	}
	void OnWindowFocusGained(fengine::FWindowEvent& e) override
	{
		std::cout << "OnWindowFocusGained()" << std::endl;
	}
	void OnWindowFocusLost(fengine::FWindowEvent& e) override
	{
		std::cout << "OnWindowFocusLost()" << std::endl;
	}
	void OnWindowClose(fengine::FWindowEvent& e) override
	{
		std::cout << "OnWindowClose()" << std::endl;
	}
};

void main_app()
{
	//fengine::FEventsManager::GetInstance()->Register<KeyboardEventsHandler>();
	//fengine::FEventsManager::GetInstance()->Register<MouseEventListener>();
	//fengine::FEventsManager::GetInstance()->Register<WindowEventListener>();
};

//FE::FJson j;
//
//j.LoadRaw("{\"kuku\": 80802, \"kaka\":{\"hi\": 123}}");
//j.SaveFile("test.json");
//
//auto t = j.FindMember("kuku");
//std::cout << t->value.GetInt() << std::endl;
//
//auto& val = j["kuku"];
//std::cout << val.GetInt() << std::endl;
//
//val.SetInt(100500);
//
//std::cout << j["kuku"].GetInt() << std::endl;
//
//auto& l = j["kaka"]["hi"];
//
//std::cout << l.GetInt() << std::endl;
//
//fengine::FSettings s;
//s.LoadDefaultSettings();
//std::cout << s.Get<int>(fengine::FSettings::SettingsNames::WindowHeight) << std::endl;
//std::cout << s.Get<int>(fengine::FSettings::SettingsNames::WindowWidth) << std::endl;
//
//s.Set<int>("param1", 5006600);
//std::cout << s.Get<int>("param1");
//s.Set<float>("param1", 1.2f);
//std::cout << s.Get<float>("param1");
//
//system("pause");
//if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
//{
//	printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
//	return -1;
//}